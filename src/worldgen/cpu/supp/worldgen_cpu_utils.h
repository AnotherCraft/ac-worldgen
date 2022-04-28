#pragma once

#include <stdint.h>

#include "util/vector.h"

class WorldGen_CPU_Utils {

public:
	static uint32_t hash(uint32_t x);
	static uint32_t hash(uint32_t x, uint32_t y);
	static uint32_t hash(const Vector2U32 &v, uint32_t seed);
	static uint32_t hash(const Vector3U32 &v, uint32_t seed);

	template<typename... Args>
	static uint32_t hashMulti(uint32_t seed, const Args& ...args) {
		uint32_t r = seed;
		((r = hash(args, r)), ...);
		return r;
	}


};

