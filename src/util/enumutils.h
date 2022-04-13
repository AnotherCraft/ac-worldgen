#pragma once

#include <type_traits>

template<typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
inline constexpr auto &operator +(T &e) noexcept {
	return reinterpret_cast<std::underlying_type_t<T> &>(e);
}

template<typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
inline constexpr auto operator +(const T &e) noexcept {
	return static_cast<std::underlying_type_t<T>>(e);
}

template<typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
inline constexpr auto operator ~(T e) noexcept {
	return ~static_cast<std::underlying_type_t<T>>(e);
}
