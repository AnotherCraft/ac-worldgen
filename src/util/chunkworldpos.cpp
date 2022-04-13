#include "chunkworldpos.h"

#include "util/blockworldpos.h"

const ChunkWorldPos ChunkWorldPos::invalid(std::numeric_limits<T>::min());

const QVector<ChunkWorldPos> &ChunkWorldPos::inclusive4NeighbourhoodOffsets() {
	static const QVector<ChunkWorldPos> result{
		ChunkWorldPos(0, 0),

		ChunkWorldPos(-1, 0),
		ChunkWorldPos(1, 0),
		ChunkWorldPos(0, -1),
		ChunkWorldPos(0, 1)
	};
	return result;
}

const QVector<ChunkWorldPos> &ChunkWorldPos::inclusive9NeighbourhoodOffsets() {
	static const QVector<ChunkWorldPos> result{
		ChunkWorldPos(0, 0),

		ChunkWorldPos(-1, 0),
		ChunkWorldPos(1, 0),
		ChunkWorldPos(0, -1),
		ChunkWorldPos(0, 1),

		ChunkWorldPos(-1, -1),
		ChunkWorldPos(-1, 1),
		ChunkWorldPos(1, -1),
		ChunkWorldPos(1, 1)
	};
	return result;
}