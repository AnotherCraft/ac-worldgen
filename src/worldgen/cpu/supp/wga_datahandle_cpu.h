#pragma once

#include "wga_valuerecs_cpu.h"
#include "worldgen/cpu/worldgenapi_cpu.h"

template<WGA_Value::ValueType type>
struct WGA_DataHandle_CPU {

public:
	using T = typename WGA_ValueRec_CPU<type>::T;

public:
	std::shared_ptr<WGA_DataRecord_CPU> handle;
	T *data = nullptr;
	size_t size = 0;
	int flag = 0;

public:
	static inline ChunkBlockIndex blockIndex(const BlockWorldPos &p) {
		return (p.x() & 0xf) | ((p.y() & 0xf) << 4) | ((p.z() & 0xf) << 8);
	}

	static inline ChunkBlockIndex blockIndex(const Vector2<BlockWorldPos_T> &p) {
		return (p.x() & 0xf) | ((p.y() & 0xf) << 4);
	}

	static inline BlockWorldPos worldPos(const BlockWorldPos &origin, int i) {
		return BlockWorldPos(origin.x() + (i & 0xf), origin.y() + ((i >> 4) & 0xf), origin.z() + (i >> 8));
	}

	static inline Vector2<BlockWorldPos_T> worldPosXY(const BlockWorldPos &origin, int i) {
		return origin.xy() + Vector2<BlockWorldPos_T>(i & 0xf, (i >> 4) & 0xf);
	}

public:
	explicit inline operator bool() const {
		return data != nullptr;
	}

	inline T &operator [](int i) const {
		return data[i & flag];
	}

	inline T &operator [](const BlockWorldPos &p) const {
		return data[blockIndex(p) & flag];
	}

	inline T &operator [](const Vector2<BlockWorldPos_T> &p) const {
		return data[blockIndex(p) & flag];
	}

};
