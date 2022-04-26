#pragma once

class HashUtils {

public:
	static void combineHash(size_t &base, size_t h) {
		base ^= h + 0x9e3779b9 + (base << 6) + (base >> 2);
	}

	template<typename... Args>
	static size_t multiHash(const Args &...args) {
		size_t r = 0;
		(combineHash(r, std::hash<Args>{}(args)), ...);
		return r;
	}

};