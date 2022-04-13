#include <QCoreApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	QCommandLineParser argp;
	argp.setApplicationDescription("AnotherCraft worldgen subsystem. After starting, the communication with the app is realized throu stdin and stdout pipes, using single-line JSON-encoded messages (with some asterisk).\nMore info on https://github.com/AnotherCraft/ac-worldgen.");
	argp.addHelpOption();

	argp.addOption({{"f", "sourceFile"}, "Source file (accepts multiple)"});
	argp.addOption({{"d", "lookupDirectory"}, "Lookup directory for resources (for example .vox files for structure generator, accepts multiple)"});
	argp.addOption({{"s", "seed"}, "Seed for the worldgen (number)"});
	argp.addOption({{"m", "mapping"}, "Block UID -> ID mapping in JSON object format.\nBlock UIDs have to be prefixed with 'block.', for example 'block.core.air'.\n\nID 0 is reserved for 'block.air'.\nID 1 is reserved for 'block.undefined'."});

	argp.process(app);

	const int result = app.exec();

	return 0;
}