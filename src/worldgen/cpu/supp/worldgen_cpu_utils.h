#pragma once

#include <stdint.h>

#include "util/vector.h"

class WorldGen_CPU_Utils {

public:
	static uint32_t hash(uint32_t x);
	static uint32_t hash(const Vector2U32 &v, uint32_t seed);
	static uint32_t hash(const Vector3U32 &v, uint32_t seed);

	static inline uint32_t hash(uint32_t x, uint32_t y) {
		return hash(hash(x) ^ y);
	}


};

