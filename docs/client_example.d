import std.stdio;
import std.process;
import std.stream;

// This code was not tested at all (hell, I don't know if it even copiles), just a demonstration of how the communication could work

void main()
{
	immutable string[] args = [
		"ac_worldgen"
		"--blockMapping", "block.stone=1,block.dirt=2",
		"--sourceFile", "world.woglac",
		"--lookupDirectory", "voxFiles",
		"--seed", "0"
	];

	// Spawn the worldgen process
	auto worldgenProcess = pipeProcess(args, Redirect.stdin | Redirect.stdout);

	// List of chunks we want to get data of
	string[] chunkRequests = [
		"0 0 0", "0 0 1", "0 0 2"
	];

	// Write all the requests to the process stdin. We want to get the data of the export named "resultBlock" of type "Block"
	foreach(string req; chunkRequests)
		worldgenProcess.stdin.writeln("getData ", req, " resultBlock Block");

	// The chunks will be asynchronously generated

	// Process the responses
	while(true) {
		int x, y, z;
		size_t payloadSize;

		// Read the response message in the given format
		worldgenProcess.stdout.readf!"data %d %d %d resultBlock %d\n"(x, y, z, payloadSize);

		// Rad the payload
		blockIDs = new ushort[payloadSize / ushort.sizeof];
		worldgenProcess.stdout.rawRead(blockIDs);

		writeln("Generated chunk ", x, " ", y, " ", z);
	}

	// Close the stdin of the worldgen to indicate it's done, the worldgen process should shut down
	worldgenProcess.stdin.close();
}
