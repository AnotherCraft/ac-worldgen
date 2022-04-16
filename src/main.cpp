#include <QtConcurrent>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThreadPool>
#include <QTextStream>
#include <QMutex>

#ifdef _WINDOWS

#include <fcntl.h>
#include <io.h>

#endif

#include "util/forit.h"
#include "util/iterators.h"

#include "worldgen/base/worldgenapi.h"

#include "worldgen/cpu/worldgenapi_cpu.h"
#include "worldgen/cpu/supp/wga_valuewrapper_cpu.h"
#include "woglac/wglcompiler.h"
#include "woglac/wglfile.h"

QMutex stdoutMutex;
QFile qstdout;

QMutex jobsMutex;
qsizetype runningJobs = 0;
bool stdinEnd = false;

void sendMessage(const QJsonObject &json, const QByteArray &payload = {}) {
	const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

	static const QByteArray newline = "\n";

	QMutexLocker _ml(&stdoutMutex);
	qstdout.write(jsonData);
	qstdout.write(newline);
	qstdout.write(payload);

	qstdout.flush();
};

void msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
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
	sendMessage(json);
};

int main(int argc, char *argv[]) {
#ifdef _WINDOWS
	// Set stdout mode to binary to prevent unwanted \n -> \r\n in binary data
	setmode(fileno(stdout), O_BINARY);
#endif

	qstdout.open(stdout, QIODevice::WriteOnly);

	qInstallMessageHandler(msgHandler);

	QCoreApplication app(argc, argv);

	QCommandLineParser argp;
	argp.setApplicationDescription("AnotherCraft worldgen subsystem. After starting, the communication with the app is realized throu stdin and stdout pipes, using single-line JSON-encoded messages (with some asterisk).\nMore info on https://github.com/AnotherCraft/ac-worldgen.");
	argp.addHelpOption();

	argp.addOption({{"f", "sourceFile"}, "Source file (accepts multiple)", "sourceFile"});
	argp.addOption({{"d", "lookupDirectory"}, "Lookup directory for resources (for example .vox files for structure generator, accepts multiple)", "lookupDirectory"});
	argp.addOption({{"s", "seed"}, "Seed for the worldgen (number)", "seed"});
	argp.addOption({{"m", "blockMapping"}, "Block UID (string) -> ID (uint16_t) mapping in JSON object format.\nBlock UIDs have to be prefixed with 'block.', for example 'block.core.air'.\n\nID 0 is reserved for 'block.air'.\nID 1 is reserved for 'block.undefined'.", "blockMapping"});
	argp.addOption({{"t", "threadCount"}, "Number of threads to use (default: min(idealThreadCount - 2, 4))", "threadCount"});
	argp.addOption({"functionList", "Emits a function list in the Markdown format and exists the application", "functionList"});
	argp.addOption({"exportList", "Compiles the source files and prints out the list of exports."});

	argp.process(app);

	// Function list export
	if(argp.isSet("functionList")) {
		QFile f(argp.value("functionList"));
		f.open(QIODevice::WriteOnly | QIODevice::Text);

		QTextStream ts(&f);
		ts << "# WOGLAC function list\n";
		ts << "Auto generated from the source code.\n\n";

		WorldGenAPI::functions().generateDocumentation(ts);

		qstdout.write(QStringLiteral("Function list exported to '%1'.\n").arg(f.fileName()).toUtf8());
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
		auto mapping = iteratorAssoc(QJsonDocument::fromJson(argp.value("blockMapping").toUtf8()).object()).mapx(std::make_pair(x.first, BlockID(x.second.toInt()))).toHash();
		mapping["block.air"] = blockID_air;
		mapping["block.undefined"] = blockID_undefined;
		wgapi.setBlockUIDMapping(mapping);
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

	if(argp.isSet("exportList")) {
		for(auto it = exports.keyValueBegin(), e = exports.keyValueEnd(); it != e; it++)
			qstdout.write(QStringLiteral("%1: %2\n").arg(it->first, WGA_Value::typeNames[it->second->valueType()]).toUtf8());

		return 0;
	}

	QThread *inputThread;
	{
		inputThread = QThread::create([&]() {
			QFile qstdin;
			qstdin.open(stdin, QIODevice::ReadOnly);

			while(true) {
				if(qstdin.atEnd()) {
					QMutexLocker _ml(&jobsMutex);
					stdinEnd = true;
					if(!runningJobs)
						qApp->quit();
					break;
				}

				QJsonParseError err;
				QByteArray msg = qstdin.readLine();

				// Get rid of unkonwn reasons null you get at the end of the string in some cases
				if(msg.endsWith(0))
					msg.chop(1);

				const QJsonObject json = QJsonDocument::fromJson(msg, &err).object();

				if(err.error != QJsonParseError::NoError) {
					qWarning() << "The command is not a valid JSON message" << err.errorString() << msg;
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
							auto h = WGA_ValueWrapper_CPU<VT>(static_cast<WGA_Value_CPU *>(val)).dataHandle(pos);
							return Data{
								.data = QByteArray(reinterpret_cast<const char *>(h.data), sizeof(WGA_ValueRec_CPU<VT>::T) * h.size),
								.recordCount = h.size
							};
						};
					};

					if(val->valueType() == WGA_Value::ValueType::Float)
						f = genf.operator ()<WGA_Value::ValueType::Float>();

					else if(val->valueType() == WGA_Value::ValueType::Block)
						f = genf.operator ()<WGA_Value::ValueType::Block>();

					else {
						qWarning() << "Unsupported export value type:" << WGA_Value::typeNames[val->valueType()];
						continue;
					}

					{
						QMutexLocker _ml(&jobsMutex);
						runningJobs++;
					}

					(void) QtConcurrent::run(&pool, [f, pos, var] {
						const Data d = f();
						const QJsonObject json{
							{"type",        "data"},
							{"export",      var},
							{"x",           pos.x()},
							{"y",           pos.y()},
							{"z",           pos.z()},
							{"payloadSize", d.data.size()},
							{"recordCount", d.recordCount},
						};

						sendMessage(json, d.data);

						{
							QMutexLocker _ml(&jobsMutex);
							runningJobs--;
							if(runningJobs == 0 && stdinEnd)
								qApp->quit();
						}
					});
				}

				else
					qWarning() << "Unknown message type:" << type;
			}
		});
		inputThread->start();
	}

	const int result = app.exec();

	inputThread->quit();
	inputThread->wait();
	delete inputThread;

	return 0;
}