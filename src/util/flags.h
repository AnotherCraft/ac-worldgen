#pragma once

#include <utility>

#undef min
#undef max

template<typename Flag, typename T = int, T defaultVal = 0>
struct Flags final {

public:
	constexpr inline Flags() {}

	//constexpr inline Flags(Flag f) : v(static_cast<T>(f)) {}
	constexpr inline Flags(const Flags &o) : v(o.v) {}

	constexpr inline Flags(Flag f) : v(static_cast<T>(f)) {}

	inline Flags(const std::initializer_list<Flag> &lst) {
		for(const auto f: lst)
			v |= static_cast<T>(f);
	}


public:
	constexpr inline bool isNull() const {
		return v == 0;
	}

	constexpr inline bool has(Flag f) const {
		return (v & static_cast<T>(f)) == static_cast<T>(f);
	}

	/// Returns if the current flags have any flags in common with $f
	constexpr inline bool intersects(Flags f) const {
		return (v & f.v) != 0;
	}

	constexpr inline Flags &set(Flag f, bool set = true) {
		v = set ? (v | static_cast<T>(f)) : (v & ~static_cast<T>(f));
		return *this;
	}

	constexpr inline Flags &set(Flags f, bool set = true) {
		v = set ? (v | f.v) : (v & ~f.v);
		return *this;
	}

	constexpr inline bool testAndSet(Flag f, bool set = true) {
		const bool r = has(f);
		v = set ? (v | static_cast<T>(f)) : (v & ~static_cast<T>(f));
		return r;
	}

	constexpr inline void clear() {
		v = defaultVal;
	}

public:
	constexpr inline Flags product(Flags o) const {
		return *this * o;
	}

public:
	constexpr inline Flags operator *(Flags o) const {
		return static_cast<T>((v | o.v) ^ ((v ^ o.v) & defaultVal));
	}

	constexpr inline Flags operator +(Flag f) const {
		return static_cast<T>(v | static_cast<T>(f));
	}

	constexpr inline Flags operator -(Flag f) const {
		return static_cast<T>(v & ~f);
	}

public:
	constexpr inline Flags operator |(Flags o) const {
		return static_cast<T>(v | o.v);
	}

	constexpr inline Flags operator &(Flags o) const {
		return static_cast<T>(v & o.v);
	}

public:
	constexpr inline Flags &operator =(Flags f) {
		v = f.v;
		return *this;
	}

	constexpr inline Flags &operator *=(Flags f) {
		(*this) = (*this) * f;
		return *this;
	}

	constexpr inline Flags &operator +=(Flag f) {
		v |= static_cast<T>(f);
		return *this;
	}

	constexpr inline Flags &operator -=(Flag f) {
		v &= ~f;
		return *this;
	}

	constexpr inline Flags &operator |=(Flag f) {
		v |= f;
		return *this;
	}

	constexpr inline Flags &operator |=(Flags f) {
		v |= f.v;
		return *this;
	}

	constexpr inline Flags &operator &=(Flag f) {
		v &= f;
		return *this;
	}

public:
	constexpr inline explicit operator bool() const {
		return v;
	}

public:
	inline T &operator +() noexcept {
		return v;
	}

	inline T operator +() const noexcept {
		return v;
	}


public:
	T v = defaultVal;

private:
	constexpr inline Flags(T v) : v(v) {}

};
