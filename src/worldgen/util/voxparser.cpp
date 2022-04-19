#include "voxparser.h"

#include <fstream>
#include <format>
#include <sstream>

template<typename T>
T readPrimitive(std::basic_istream<char> &stream) {
	T result;
	stream.read(reinterpret_cast<char *>(&result), sizeof(result));

	if(!stream.good())
		throw "Invalid data (RP)";

	return result;
}

void VOXParser::parseFile(const std::string &file) {
	std::ifstream f;
	f.open(file, std::ios::in);

	if(!f.good())
		throw std::format("Could not open VOX file '{}' for reading.", file);

	parseData(f);
}

void VOXParser::parseData(std::basic_istream<char> &stream) {
	clear();

	std::string prefix;
	prefix.resize(4);
	stream.read(prefix.data(), prefix.size());
	if(prefix != "VOX ")
		throw "Provided file is not of the VOX file format";

	const auto fileVersion = readPrimitive<uint32_t>(stream);
	if(fileVersion != 150)
		throw std::format("Unsupported vox file format version ({})", fileVersion);

	// Process main chunk
	{
		const Chunk mainChunk = readChunk(stream);
		if(mainChunk.name != "MAIN")
			throw "MAIN chunk expected";

		char c;
		stream.read(&c, 1);
		if(!stream.eof())
			throw "There should be nothing left after the main chunk";

		if(!mainChunk.data.empty())
			throw "Main chunk should not have any data";

		std::istringstream mb(mainChunk.childrenChunks);

		while(!mb.eof()) {
			const Chunk ch = readChunk(mb);

			if(!ch.childrenChunks.empty())
				throw "Invalid data (3)";

			std::istringstream cb(ch.data);

			if(ch.name == "XYZI") {
				struct VoxelRec {
					uint8_t x, y, z, id;
				};

				if(!voxels_.empty())
					throw "Multiple models are not supported";

				auto numVoxels = readPrimitive<uint32_t>(cb);
				while(numVoxels--) {
					const VoxelRec voxel = readPrimitive<VoxelRec>(cb);
					voxels_[voxel.id].push_back(VoxelPos{voxel.x, voxel.y, voxel.z});
				}
			}

				// We don't care about other chunk types
			else
				continue;

			if(!cb.eof())
				throw "Invalid data (4)";
		}
	}
}

void VOXParser::clear() {
	voxels_.clear();
}

VOXParser::Chunk VOXParser::readChunk(std::basic_istream<char> &b) {

	Chunk chunk;

	chunk.name.resize(4);
	b.read(chunk.name.data(), chunk.name.size());

	const auto dataSize = readPrimitive<uint32_t>(b);
	const auto childrenSize = readPrimitive<uint32_t>(b);

	chunk.data.resize(dataSize);
	b.read(chunk.data.data(), dataSize);

	chunk.childrenChunks.resize(childrenSize);
	b.read(chunk.childrenChunks.data(), childrenSize);

	if(b.eof())
		throw "Invalid data";

	return chunk;
}
