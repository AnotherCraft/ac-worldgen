#pragma once

#include <limits>

#include "util/vector.h"

/**
 * @brief Vector for storing position of a chunk.
 */
class ChunkWorldPos : public Vector2<BlockWorldPos_T> {

public:
	using V = Vector2<BlockWorldPos_T>;

public:
	static const QVector<ChunkWorldPos> &inclusive4NeighbourhoodOffsets();
	static const QVector<ChunkWorldPos> &inclusive9NeighbourhoodOffsets();

	static const ChunkWorldPos invalid;

public:
	inline constexpr ChunkWorldPos() = default;

	inline constexpr ChunkWorldPos(T v) : V(v) {}

	inline constexpr ChunkWorldPos(T x, T y) : V(x, y) {}

	inline constexpr ChunkWorldPos(const V &other) : V(other) {}

	static inline constexpr ChunkWorldPos fromEntityPos(const V3F &v) {
		return {static_cast<BlockWorldPos_T>(v.x()) >> 4, static_cast<BlockWorldPos_T>(v.y()) >> 4};
	}

public:
	inline bool isValid() const {
		return *this != invalid;
	}

public:
	inline V operator +(const V &v) const {
		return V(x() + v.x(), y() + v.y());
	}

};

inline size_t qHash(const ChunkWorldPos &v, size_t seed) {
	return qHash(static_cast<ChunkWorldPos::V>(v), seed);
}
