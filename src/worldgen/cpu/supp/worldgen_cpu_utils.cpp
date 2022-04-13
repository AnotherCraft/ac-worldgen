#include "worldgen_cpu_utils.h"

uint32_t WorldGen_CPU_Utils::hash(uint32_t x) {
	x *= 0xcc9e2d51;
	x = (x << 15) | (x >> 17);
	x *= 0x1b873593;
	return x;
}

uint32_t WorldGen_CPU_Utils::hash(const Vector2U32 &v, uint32_t seed) {
	uint32_t result = hash(seed ^ v.x());
	result = hash(result ^ v.y());
	return result;
}

uint32_t WorldGen_CPU_Utils::hash(const Vector3U32 &v, uint32_t seed) {
	uint32_t result = hash(seed ^ v.x());
	result = hash(result ^ v.y());
	result = hash(result ^ v.z());
	return result;
}
