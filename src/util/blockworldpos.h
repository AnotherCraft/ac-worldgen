#pragma once

#include "util/vector.h"
#include "util/chunkworldpos.h"
#include "util/hashutils.h"

class BlockWorldPos : public Vector3<BlockWorldPos_T> {

public:
	using V = Vector3<BlockWorldPos_T>;

public:
	constexpr inline BlockWorldPos() = default;

	constexpr inline BlockWorldPos(T v) : V(v) {}

	constexpr inline BlockWorldPos(T x, T y, T z) : V(x, y, z) {}

	constexpr inline BlockWorldPos(const V &other) : V(other) {}

	static inline BlockWorldPos fromChunkBlockIndex(const ChunkWorldPos &chunkPos, BlockWorldPos_T chunkZOffset, ChunkBlockIndex ix) {
		return BlockWorldPos(
			(chunkPos.x() << 4) | (ix & 0xf),
			(chunkPos.y() << 4) | ((ix >> 4) & 0xf),
			chunkZOffset + (ix >> 8)
		);
	}

public:
	/// Returns position of the chunk corresponding to the given block position
	inline ChunkWorldPos chunkPosition() const {
		return ChunkWorldPos(x() >> 4, y() >> 4);
	}

	/// Returns position local to the chunk offset
	inline BlockWorldPos chunkLocalPosition(BlockWorldPos_T chunkZOffset) const {
		return BlockWorldPos(
			x() & 0xf,
			y() & 0xf,
			z() - chunkZOffset
		);
	}

	/// Returns index of the block in chunk arrays
	inline ChunkBlockIndex chunkBlockIndex(BlockWorldPos_T chunkZOffset) const {
		return static_cast<ChunkBlockIndex>(
			(x() & 0xf)
			| ((y() & 0xf) << 4)
			| ((z() - chunkZOffset) << 8)
		);
	}

	/// Returns index of the block in chunk arrays
	inline ChunkBlockIndex subChunkBlockIndex(BlockWorldPos_T chunkZOffset) const {
		return static_cast<ChunkBlockIndex>(
			(x() & 0xf)
			| ((y() & 0xf) << 4)
			| (((z() - chunkZOffset) & 0xf) << 8)
		);
	}

	inline V3F blockCenter() const {
		return this->to<float>() + 0.5f;
	}

	inline bool isVerticallyOutsideChunk(BlockWorldPos_T chunkZOffset) const {
		return z() < chunkZOffset || z() >= chunkZOffset + chunkSize;
	}

};

template<>
struct std::hash<BlockWorldPos> {
	size_t operator ()(const BlockWorldPos &v) const {
		return HashUtils::multiHash(v.x(), v.y(), v.z());
	}
};


