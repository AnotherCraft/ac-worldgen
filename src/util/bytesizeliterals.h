#pragma once

inline constexpr int operator "" _MB(unsigned long long int val) {
	return static_cast<int>(val * 1024 * 1024);
}

inline constexpr int operator "" _kB(unsigned long long int val) {
	return static_cast<int>(val * 1024);
}
