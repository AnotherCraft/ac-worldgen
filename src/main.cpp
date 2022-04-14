#include <QtConcurrent>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThreadPool>
#include <QTextStream>

#include "util/forit.h"
#include "util/iterators.h"

#include "worldgen/base/worldgenapi.h"

#include "worldgen/cpu/worldgenapi_cpu.h"
#include "worldgen/cpu/supp/wga_valuewrapper_cpu.h"
#include "woglac/wglcompiler.h"
#include "woglac/wglfile.h"

QFile qstdout;

int main(int argc, char *argv[]) {
	qstdout.open(stdout, QIODevice::WriteOnly);

	const auto msgHandler = +[](QtMsgType type, const QMessageLogContext &context, const QString &msg) {
		static const QHash<int, QString> msgs{
			{+QtMsgType::QtWarningMsg,  "error"},
			{+QtMsgType::QtCriticalMsg, "error"},
			{+QtMsgType::QtFatalMsg,    "error"},
		};

		const QJsonObject json{
			{"type",     "message"},
			{"severity", msgs.value(+type, "info")},
			{"message",  msg},
		};

		qstdout.write(QJsonDocument(json).toJson(QJsonDocument::Compact));
		qstdout.write("\n");
	};
	qInstallMessageHandler(msgHandler);

	QCoreApplication app(argc, argv);

	QCommandLineParser argp;
	argp.setApplicationDescription("AnotherCraft worldgen subsystem. After starting, the communication with the app is realized throu stdin and stdout pipes, using single-line JSON-encoded messages (with some asterisk).\nMore info on https://github.com/AnotherCraft/ac-worldgen.");
	argp.addHelpOption();

	argp.addOption({{"f", "sourceFile"}, "Source file (accepts multiple)", "sourceFile"});
	argp.addOption({{"d", "lookupDirectory"}, "Lookup directory for resources (for example .vox files for structure generator, accepts multiple)", "lookupDirectory"});
	argp.addOption({{"s", "seed"}, "Seed for the worldgen (number)", "seed"});
	argp.addOption({{"m", "blockMapping"}, "Block UID -> ID mapping in JSON object format.\nBlock UIDs have to be prefixed with 'block.', for example 'block.core.air'.\n\nID 0 is reserved for 'block.air'.\nID 1 is reserved for 'block.undefined'.", "blockMapping"});
	argp.addOption({{"t", "threadCount"}, "Number of threads to use (default: min(idealThreadCount - 2, 4))", "threadCount"});
	argp.addOption({"functionList", "Emits a function list in the Markdown format and exists the application", "functionList"});

	argp.process(app);

	// Function list export
	if(argp.isSet("functionList")) {
		QFile f(argp.value("functionList"));
		f.open(QIODevice::WriteOnly | QIODevice::Text);

		QTextStream ts(&f);
		ts << "# WOGLAC function list\n";
		ts << "Auto generated from the source code.\n\n";

		WorldGenAPI::functions().generateDocumentation(ts);

		qInfo() << "Function list exported to " << f.fileName();
		return 0;
	}

	QThreadPool pool;
	{
		int threadCount = argp.value("threadCount").toInt();
		if(threadCount <= 0)
			threadCount = qBound(1, QThread::idealThreadCount() - 2, 4);

		pool.setMaxThreadCount(threadCount);
	}

	// Setup WorldGenAPI
	WorldGenAPI_CPU wgapi;
	{
		// Seed
		if(argp.isSet("seed"))
			wgapi.setSeed(WorldGenSeed(argp.value("seed").toLongLong()));

		// Block mapping
		wgapi.setBlockUIDMapping(iteratorAssoc(QJsonDocument::fromJson(argp.value("blockMapping").toUtf8()).object()).mapx(std::make_pair(x.first, BlockID(x.second.toInt()))).toHash());
	}

	// Compile source files
	QHash<QString, WGA_Value *> exports;
	{
		WGLCompiler wgc;

		wgc.setLookupDirectories(argp.values("lookupDirectory"));

		for(const QString &filename: argp.values("sourceFile"))
			wgc.addFile(WGLFilePtr(new WGLFile(filename)));

		wgc.compile();
		exports = wgc.construct(wgapi);
	}

	QFile qstdin;
	{
		qstdin.open(stdin, QIODevice::ReadOnly | QIODevice::Text);
		const auto readCommands = [&]() {
			while(qstdin.bytesAvailable()) {
				QJsonParseError err;
				const QJsonObject json = QJsonDocument::fromJson(qstdin.readLine(), &err).object();

				if(err.error != QJsonParseError::NoError) {
					qWarning() << "The command is not a valid JSON message" << err.errorString();
					continue;
				}

				const QString type = json["type"].toString();
				if(type == "getData") {
					const BlockWorldPos pos = Vector3<double>(json["x"].toDouble(), json["y"].toDouble(), json["z"].toDouble()).to<BlockWorldPos_T>() & ~blockInChunkPosMask;

					const QString var = json["export"].toString();
					WGA_Value *val = exports.value(var);
					if(!val) {
						qWarning() << "Export does not exist: " << var;
						continue;
					}

					if(val->symbolType() != WGA_Value::SymbolType::Value) {
						qWarning() << "Export symbol is not a variable";
						continue;
					}

					if(WGA_Value::typeNames[val->valueType()] != json["valueType"].toString()) {
						qWarning() << QStringLiteral("Export '%1' is of type '%2', but '%3' expected").arg(var, WGA_Value::typeNames[val->valueType()], json["valueType"].toString());
						continue;
					}

					struct Data {
						QByteArray data;
						qsizetype recordCount;
					};
					std::function<Data()> f;

					const auto genf = [val, pos]<WGA_Value::ValueType VT>() {
						return [val, pos] {
							auto h = WGA_ValueWrapper_CPU<WGA_Value::ValueType::Float>(static_cast<WGA_Value_CPU *>(val)).dataHandle(pos);
							return Data{
								.data = QByteArray(reinterpret_cast<const char *>(h.data), sizeof(decltype(h)::T) * h.size),
								.recordCount = h.size
							};
						};
					};

					if(val->valueType() == WGA_Value::ValueType::Float)
						f = genf.operator ()<WGA_Value::ValueType::Float>();
					else if(val->valueType() == WGA_Value::ValueType::Block)
						f = genf.operator ()<WGA_Value::ValueType::Block>();
					else
						qWarning() << "Unsupported export value type:" << WGA_Value::typeNames[val->valueType()];

					(void) QtConcurrent::run(&pool, [f, pos] {
						const Data d = f();
						const QJsonObject json{
							{"type",  "data"},
							{"x",     pos.x()},
							{"y",     pos.y()},
							{"z",     pos.z()},
							{"size",  d.data.size()},
							{"count", d.recordCount},
						};

						QTimer::singleShot(0, qApp, [json, payload = d.data] {
							qstdout.write(QJsonDocument(json).toJson(QJsonDocument::Compact));
							qstdout.write("\n");
							qstdout.write(payload);
						});
					});
				}
				else
					qWarning() << "Unknown message type:" << type;
			}
		};

		QObject::connect(&qstdin, &QIODevice::readyRead, &app, readCommands);
	}


	const int result = app.exec();

	return 0;
}