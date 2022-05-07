#include "voxparser.h"

#include <fstream>
#include <format>
#include <sstream>

template<typename T>
T readPrimitive(std::basic_istream<char> &stream) {
	T result = {};
	stream.read(reinterpret_cast<char *>(&result), sizeof(result));

	if(!stream.good())
		throw std::exception(std::format("Invalid data (RP) {}", stream.gcount()).c_str());

	return result;
}

void VOXParser::parseData(std::basic_istream<char> &stream) {
	clear();

	std::string prefix;
	prefix.resize(4);
	stream.read(prefix.data(), prefix.size());
	if(prefix != "VOX ")
		throw std::exception("Provided file is not of the VOX file format");

	const auto fileVersion = readPrimitive<uint32_t>(stream);
	if(fileVersion != 150 && fileVersion != 200)
		throw std::exception(std::format("Unsupported vox file format version ({})", fileVersion).c_str());

	// Process main chunk
	{
		const Chunk mainChunk = readChunk(stream);
		if(mainChunk.name != "MAIN")
			throw std::exception("MAIN chunk expected");

		if(stream.peek() != EOF)
			throw std::exception("There should be nothing left after the main chunk");

		if(!mainChunk.data.empty())
			throw std::exception("Main chunk should not have any data");

		std::istringstream mb(mainChunk.childrenChunks);

		while(mb.peek() != EOF) {
			const Chunk ch = readChunk(mb);

			if(!ch.childrenChunks.empty())
				throw std::exception("Invalid data (3)");

			std::istringstream cb(ch.data);

			if(ch.name == "XYZI") {
				struct VoxelRec {
					uint8_t x, y, z, id;
				};

				if(!voxels_.empty())
					throw std::exception("Multiple models are not supported");

				auto numVoxels = readPrimitive<uint32_t>(cb);
				while(numVoxels--) {
					const VoxelRec voxel = readPrimitive<VoxelRec>(cb);
					voxels_[voxel.id].push_back(VoxelPos{voxel.x, voxel.y, voxel.z});
				}
			}

				// We don't care about other chunk types
			else
				continue;

			if(cb.peek() != EOF)
				throw std::exception("Invalid data (4)");
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

	auto pos = b.tellg();
	b.seekg(0, std::ios_base::end);
	auto len = b.tellg();
	b.seekg(pos);

	chunk.data.resize(dataSize);
	b.read(chunk.data.data(), dataSize);

	chunk.childrenChunks.resize(childrenSize);
	b.read(chunk.childrenChunks.data(), childrenSize);

	if(!b.good())
		throw std::exception("Invalid data (unexpected EOF)");

	return chunk;
}
