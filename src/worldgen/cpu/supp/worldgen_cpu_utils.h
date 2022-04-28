#pragma once

#include <stdint.h>

#include "util/vector.h"

class WorldGen_CPU_Utils {

public:
	static inline uint32_t scramble(uint32_t x) {
		// Murmur scramble
		x *= 0xcc9e2d51;
		x = (x << 15) | (x >> 17);
		x *= 0x1b873593;
		return x;
	}

	template<typename... Args>
	static uint32_t hashMulti(uint32_t seed, const Args& ...args) {
		uint32_t h = scramble(seed);

		const auto f = [&] (const auto &v) {
			h = hash(v, h);
		};

		(f(args), ...);

		// Finalize
		h ^= h >> 16;
		h *= 0x85ebca6b;
		h ^= h >> 13;
		h *= 0xc2b2ae35;
		h ^= h >> 16;

		return h;
	}

	static inline uint32_t hash(uint32_t v, uint32_t seed) {
		uint32_t h = seed;
		h ^= scramble(v);
		h = (h << 13) | (h >> 19);
		h = h * 5 + 0xe6546b64;
		return h;
	}

	static inline uint32_t hash(const Vector2U32 &v, uint32_t seed) {
		return hashMulti(seed, v.x(), v.y());
	}
	static uint32_t hash(const Vector3U32 &v, uint32_t seed) {
		return hashMulti(seed, v.x(), v.y(), v.z());
	}





};

