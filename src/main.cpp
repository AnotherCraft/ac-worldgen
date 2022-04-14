#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>

#include "worldgen/base/worldgenapi.h"

#include "worldgen/cpu/worldgenapi_cpu.h"
#include "woglac/wglcompiler.h"
#include "woglac/wglfile.h"

std::unique_ptr<WorldGenAPI_CPU> wapi;

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	QCommandLineParser argp;
	argp.setApplicationDescription("AnotherCraft worldgen subsystem. After starting, the communication with the app is realized throu stdin and stdout pipes, using single-line JSON-encoded messages (with some asterisk).\nMore info on https://github.com/AnotherCraft/ac-worldgen.");
	argp.addHelpOption();

	argp.addOption({{"f", "sourceFile"}, "Source file (accepts multiple)", "sourceFile"});
	argp.addOption({{"d", "lookupDirectory"}, "Lookup directory for resources (for example .vox files for structure generator, accepts multiple)", "lookupDirectory"});
	argp.addOption({{"s", "seed"}, "Seed for the worldgen (number)", "seed"});
	argp.addOption({{"m", "mapping"}, "Block UID -> ID mapping in JSON object format.\nBlock UIDs have to be prefixed with 'block.', for example 'block.core.air'.\n\nID 0 is reserved for 'block.air'.\nID 1 is reserved for 'block.undefined'.", "mapping"});
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

	// Compile source files
	{
		WGLCompiler wgc;

		for(const QString &filename: argp.values("sourceFile"))
			wgc.addFile(WGLFilePtr(new WGLFile(filename)));

		wgc.compile();
	}

	const int result = app.exec();

	return 0;
}