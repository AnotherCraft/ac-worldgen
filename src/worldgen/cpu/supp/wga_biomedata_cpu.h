#pragma once

#include <stdint.h>

struct WGA_BiomeData_CPU {

public:
	static constexpr int gridSize = 256;
	static constexpr int maxCountComp = 5;
	static constexpr int maxCount = maxCountComp * maxCountComp;

public:
	WGA_Biome *biomes[maxCount] = {nullptr};
	uint8_t nearestBiomes[chunkSurface] = {0};
	float weight[chunkSurface][maxCount] = {{0}};
	int count = 0;

public:
	void calculateFor(WorldGenAPI_CPU &api, const BlockWorldPos &pos);

};

