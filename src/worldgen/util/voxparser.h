#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>

/// Parser of the VOX file format
/// File format specified here: https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt
class VOXParser {

public:
	struct VoxelPos {
		uint8_t x, y, z;
	};

public:
	void parseFile(const std::string &filePath);
	void parseData(std::basic_istream<char> &stream);

public:
	inline const auto &voxels() const {
		return voxels_;
	}

	inline bool isEmpty() const {
		return voxels_.empty();
	}

	void clear();

private:
	struct Chunk {
		std::string name;
		std::string data;
		std::string childrenChunks;
	};

private:
	Chunk readChunk(std::basic_istream<char> &b);

private:
	std::unordered_map<uint8_t, std::vector<VoxelPos>> voxels_;

};

