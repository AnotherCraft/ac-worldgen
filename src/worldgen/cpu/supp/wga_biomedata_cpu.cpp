#include "wga_biomedata_cpu.h"

#include "worldgen/cpu/worldgenapi_cpu.h"
#include "worldgen_cpu_utils.h"

void WGA_BiomeData_CPU::calculateFor(WorldGenAPI_CPU &api, const BlockWorldPos &pos) {
	static constexpr int gridSizeMask = gridSize - 1;

	const Vector2I gridNode(pos.x() & ~gridSizeMask, pos.y() & ~gridSizeMask);

	WGA_Biome *rawBiomes[maxCount];
	Vector2I nodeRelPositions[maxCount];

	const uint32_t seed = api.seed();

	for(int i = 0; i < maxCount; i++) {
		const Vector2I relPos = Vector2I(-gridSize * 2) + Vector2I(i % maxCountComp, i / maxCountComp) * gridSize;
		const Vector2I baseWorldPos = gridNode + relPos;

		const uint32_t bhash = WorldGen_CPU_Utils::hash(
			WorldGen_CPU_Utils::hash(seed ^ baseWorldPos.x()) ^ baseWorldPos.y());
		const Vector2I baseWorldPosOffset = Vector2I(bhash & gridSizeMask, WorldGen_CPU_Utils::hash(bhash ^ 8455123) & gridSizeMask);
		const Vector2I worldPos = baseWorldPos + baseWorldPosOffset;

		rawBiomes[i] = &api.getChunkBiome(BlockWorldPos(worldPos.x() & ~blockInChunkPosMask, worldPos.y() & ~blockInChunkPosMask, 0));
		nodeRelPositions[i] = relPos + baseWorldPosOffset;
	}

	int rawBiomeMapping[maxCount];
	for(int i = 0; i < maxCount; i++) {
		WGA_Biome *biome = rawBiomes[i];
		bool found = false;

		for(int j = 0; j < i; j++) {
			if(biome == biomes[j]) {
				found = true;
				rawBiomeMapping[i] = j;
				break;
			}
		}

		if(!found) {
			biomes[count] = biome;
			rawBiomeMapping[i] = count++;
		}
	}

	for(int i = 0; i < chunkSurface; i++) {
		const Vector2I gridRelPos = (pos.xy() & gridSizeMask) + Vector2I(i % chunkSize, i / chunkSize);

		int winningBiome = -1;
		float largestWeight = std::numeric_limits<float>::lowest();

		float weights[maxCount] = {0};
		for(int j = 0; j < maxCount; j++) {
			const Vector2I diff = (gridRelPos - nodeRelPositions[j]).abs();
			const float distance = sqrt(static_cast<float>(diff.dotProduct(diff)));

			const int biomeId = rawBiomeMapping[j];
			float &weight = weights[biomeId];
			weight += qMax<float>(0, 1 - distance / (gridSize * 1.42f));

			if(weight > largestWeight) {
				largestWeight = weight;
				winningBiome = biomeId;
			}
		}

		for(int j = 0; j < 9; j++)
			weight[i][j] = weights[j];

		ASSERT(winningBiome != -1);
		nearestBiomes[i] = static_cast<uint8_t>(winningBiome);
	}
}
