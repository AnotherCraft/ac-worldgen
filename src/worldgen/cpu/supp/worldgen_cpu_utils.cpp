#include "worldgen_cpu_utils.h"

uint32_t WorldGen_CPU_Utils::hash(uint32_t x) {
	x += (x << 3);
	x ^= (x >> 11);
	x += (x << 15);
	return x;
}

uint32_t WorldGen_CPU_Utils::hash(uint32_t x, uint32_t y) {
	auto *p = reinterpret_cast<unsigned char*>(&x);
	for (int i = 0; i < sizeof(x); i++) {
		y += p[i];
		y += (y << 10);
		y ^= (y >> 6);
	}

	return y;
}

uint32_t WorldGen_CPU_Utils::hash(const Vector2U32 &v, uint32_t seed) {
	uint32_t result = hash(seed ^ v.x());
	result = hash(result ^ v.y());
	return result;
}

uint32_t WorldGen_CPU_Utils::hash(const Vector3U32 &v, uint32_t seed) {
	uint32_t result = seed;
	result = hash(v.x(), result);
	result = hash(v.y(), result);
	result = hash(v.z(), result);
	result = hash(result);
	return result;
}
