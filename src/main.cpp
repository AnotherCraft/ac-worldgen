#include <mutex>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <format>
#include <string>
#include <queue>

#ifdef _WINDOWS

#include <fcntl.h>
#include <io.h>

#endif

#include "util/forit.h"
#include "util/iterators.h"
#include "util/tracyutils.h"

#include "worldgen/base/worldgenapi.h"

#include "worldgen/cpu/worldgenapi_cpu.h"
#include "worldgen/cpu/supp/wga_valuewrapper_cpu.h"
#include "woglac/wglcompiler.h"
#include "woglac/wglfile.h"

std::mutex stdoutMutex;

std::mutex jobsMutex;
std::condition_variable jobEndCondition, newJobCondition;
std::queue<std::function<void()>> jobs;
size_t runningJobs = 0;

int main(int argc, char *argv[]) {
#ifdef _WINDOWS
	// Set stdout mode to binary to prevent unwanted \n -> \r\n in binary data
	setmode(fileno(stdout), O_BINARY);
#endif

	std::vector<std::thread> pool;

	try {
		std::vector<std::string> files, lookupDirs;
		std::unordered_map<std::string, BlockID> blockMapping;
		size_t seed = 0;
		size_t threadCount = std::min<size_t>(std::thread::hardware_concurrency() - 2, 4);
		bool exportList = false;
		bool showHelp = argc < 2;

		size_t argi = 1;
		const auto popArg = [&](const std::string &def = {}) {
			return (argi >= argc) ? def : std::string(argv[argi++]);
		};

		while(argi < argc) {
			const std::string arg = popArg();
			if(arg == "-f" || arg == "--sourceFile")
				files.push_back(popArg());

			else if(arg == "-d" || arg == "--lookupDirectory")
				lookupDirs.push_back(popArg());

			else if(arg == "-s" || arg == "--seed")
				seed = std::stoi(popArg());

			else if(arg == "-m" || arg == "--blockMapping") {
				const std::string str = popArg();
				size_t offset = 0;
				while(true) {
					const size_t eqsep = str.find('=', offset);
					if(eqsep == std::string::npos)
						break;

					const size_t endsep = str.find(',', eqsep);

					const std::string uid = str.substr(offset, eqsep - offset);
					const BlockID id = (BlockID) std::stoi(str.substr(eqsep + 1, endsep));

					blockMapping.insert_or_assign(uid, id);

					if(endsep == std::string::npos)
						break;

					offset = endsep + 1;
				}
			}

			else if(arg == "-t" || arg == "--threadCount")
				threadCount = stoi(popArg());

			else if(arg == "--functionList") {
				std::cout << "# WOGLAC function list\n";
				std::cout << "Auto generated from the source code.\n\n";

				WorldGenAPI::functions().generateDocumentation();
				return 0;
			}

			else if(arg == "--exportList")
				exportList = true;

			else if(arg == "--help" || arg == "-h")
				showHelp = true;

			else {
				std::cout << std::format("Unknown parameter '{}'.\n", arg);
				return 1;
			}
		}

		if(showHelp) {
			std::cout << "AnotherCraft worldgen subsystem. After starting, the communication with the app is realized throu stdin and stdout pipes, using single-line JSON-encoded messages (with some asterisk).\nMore info on https://github.com/AnotherCraft/ac-worldgen.\n";
			std::cout << "\n\nUsage: ac-worldgen (args)\n\n";

			std::cout << "-f <f> | --sourceFile <f>\nSource file (accepts multiple).\n\n";
			std::cout << "-d <d> | --lookupDirectory <d>\nLookup directory for resources (for example .vox files for structure generator, accepts multiple).\n\n";
			std::cout << "-s <s> | --seed <s>\nSeed for the worldgen (number).\n\n";
			std::cout << "-m <m> | --blockMapping <m>\nBlock UID (string) -> ID (uint16_t) mapping in format 'uid=id,uid2=id2,uid3=id3'.\nBlock UIDs have to be prefixed with 'block.', for example 'block.core.air'.\nID 0 is reserved for 'block.air'.\nID 1 is reserved for 'block.undefined'.\n\n";
			std::cout << "--functionList\nEmits a function list in the Markdown format.";
			std::cout << "--exportList\nCompiles the source files and prints out the list of exports.";
			return 0;
		}

		// Setup WorldGenAPI
		WorldGenAPI_CPU wgapi;
		{
			wgapi.setSeed(WorldGenSeed(seed));

			// Block mapping
			blockMapping["block.air"] = blockID_air;
			blockMapping["block.undefined"] = blockID_undefined;
			wgapi.setBlockUIDMapping(blockMapping);
		}

		// Compile source files
		std::unordered_map<std::string, WGA_Value *> exports;
		{
			WGLCompiler wgc;

			wgc.setLookupDirectories(lookupDirs);

			for(const std::string &filename: files)
				wgc.addFile(std::make_shared<WGLFile>(filename));

			wgc.compile();
			exports = wgc.construct(wgapi);
		}

		if(exportList) {
			for(auto it = exports.begin(), e = exports.end(); it != e; it++)
				std::cout << std::format("%1: %2\n", it->first, WGA_Value::typeNames.at(it->second->valueType()));

			return 0;
		}

		for(size_t i = 0; i < threadCount; i++) {
			pool.push_back(std::thread([] {
				while(true) {
					std::function < void() > job;

					{
						std::unique_lock lock(jobsMutex);
						while(jobs.empty())
							newJobCondition.wait(lock);

						job = jobs.front();
						jobs.pop();
					}

					try {
						job();
					}
					catch(const std::exception &e) {
						std::cerr << e.what() << "\n";
					}

					{
						std::unique_lock lock(jobsMutex);
						runningJobs--;
						jobEndCondition.notify_all();
					}
				}
			}));
		}

		// Main stdin loop
		while(true) {
			std::string type;
			std::cin >> type;

			if(type.empty() && std::cin.eof())
				break;

			if(type == "getData") {
				BlockWorldPos pos;
				std::cin >> pos.x() >> pos.y() >> pos.z();
				pos = pos & ~blockInChunkPosMask;

				std::string var;
				std::cin >> var;
				const auto valp = exports.find(var);
				if(valp == exports.end()) {
					std::unique_lock _l(stdoutMutex);
					std::cerr << "Export does not exist: " << var << "\n";
					continue;
				}
				WGA_Value *val = valp->second;

				if(val->symbolType() != WGA_Value::SymbolType::Value) {
					std::unique_lock _l(stdoutMutex);
					std::cerr << "Export symbol is not a variable\n";
					continue;
				}

				std::string valueType;
				std::cin >> valueType;
				if(WGA_Value::typeNames.at(val->valueType()) != valueType) {
					std::unique_lock _ul(stdoutMutex);
					std::cerr << std::format("Export '{}' is of type '{}', but '{}' expected.\n", var, WGA_Value::typeNames.at(val->valueType()), valueType);
					return 1;
				}

				struct Data {
					std::vector<char> data;
					size_t recordCount;
				};
				std::function < Data() > f;

				const auto genf = [val, pos]<WGA_Value::ValueType vt>() {
					return [val, pos] {
						ZoneScopedN("getData");

						auto h = WGA_ValueWrapper_CPU<vt>(static_cast<WGA_Value_CPU *>(val)).dataHandle(pos);
						Data r{
							.recordCount = h.size
						};

						/*if constexpr(vt == WGA_Value::ValueType::Block) {
							for(size_t i = 0; i < h.size; i++)
								if(h.data[i] == blockID_undefined)
									__debugbreak();
						}*/

						const size_t bytes = sizeof(WGA_ValueRec_CPU<vt>::T) * h.size;
						r.data.resize(bytes);
						memcpy(r.data.data(), reinterpret_cast<const char *>(h.data), bytes);
						return r;
					};
				};

				if(val->valueType() == WGA_Value::ValueType::Float)
					f = genf.operator ()<WGA_Value::ValueType::Float>();

				else if(val->valueType() == WGA_Value::ValueType::Block)
					f = genf.operator ()<WGA_Value::ValueType::Block>();

				else {
					std::unique_lock _l(stdoutMutex);
					std::cerr << std::format("Unsupported export value type: {}", WGA_Value::typeNames.at(val->valueType()));
					return 1;
				}

				const auto job = [f, pos, var] {
					const Data d = f();
					std::unique_lock _ul(stdoutMutex);

					std::cout << std::format("data {} {} {} {} {}\n", pos.x(), pos.y(), pos.z(), var, d.data.size());
					std::cout.write(d.data.data(), d.data.size());
					std::cout.flush();
				};

				{
					std::unique_lock _ml(jobsMutex);
					runningJobs++;
					jobs.push(job);
					newJobCondition.notify_one();
				}
			}

			else
				throw std::exception(std::format("Unknown message type: {}", type).c_str());

		}


		{
			std::unique_lock l(jobsMutex);
			while(runningJobs)
				jobEndCondition.wait(l);
		}

		{
			for(std::thread &t: pool)
				t.detach();
		}

	}
	catch(const std::exception &e) {
		std::cerr << e.what() << "\n";
		for(std::thread &t: pool)
			t.detach();
		return 1;
	}

	return 0;
}