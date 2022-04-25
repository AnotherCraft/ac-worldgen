#pragma once

#include <type_traits>
#include <math.h>
#include <random>
#include <format>

#include "util/assert.h"
#include "util/hashutils.h"
#include "util/iterators.h"

#define VECTOR_COMPONENT_OP(expr) Vector<T, D> result; for(int i = 0; i < D; i++) result[i] = expr; return result
#define VECTOR_COMPONENT_OP_RT(RT, expr) RT result; for(int i = 0; i < D; i++) result[i] = expr; return result
#define VECTOR_SELF_COMPONENT_OP(expr) for(int i = 0; i < D; i++) data[i] = expr;

template<typename T_, int D_>
class Vector;

template<typename T_, int D_>
class _VectorBase;

template<int D>
constexpr inline float length(const Vector<float, D> &v) {
	return v.length();
}

inline float length(float v) {
	return abs(v);
}

template<typename T>
constexpr inline Vector<T, 1> toVector(const T &v) {
	return Vector<T, 1>(v);
}

template<typename T, int D>
constexpr inline Vector<T, D> toVector(const Vector<T, D> &v) {
	return v;
}

template<typename T, typename A1>
constexpr inline auto concatVectors(const A1 &v) {
	return toVector<T>(v);
}

template<typename T, typename A1, typename A2, typename ...Args>
constexpr inline auto concatVectors(const A1 &a1, const A2 &a2, Args &&...args) {
	const auto v1 = toVector<T>(a1);
	const auto v2 = toVector<T>(a2);

	using V1 = decltype(v1);
	using V2 = decltype(v2);

	Vector<typename V1::T, V1::D + V2::D> result;
	for(int i = 0; i < v1.D; i++)
		result[i] = v1[i];

	for(int i = 0; i < v2.D; i++)
		result[i + v1.D] = v2[i];

	return concatVectors<T>(result, std::forward<Args>(args)...);
}

template<typename T_, int D_>
class _VectorBase {

public:
	using T = T_;
	static constexpr int D = D_;
	using V = Vector<T, D>;
	using VB = Vector<bool, D>;

public:
	template<typename RNG>
	static V randomUnitVector(RNG &rng) {
		std::normal_distribution<T> dst(0, 1);
		V r;
		for(auto &v: r.data) v = dst(rng);
		return r.normalized();
	}

public: // Components
	constexpr inline T &x() {
		return operator [](0);
	}

	constexpr inline const T &x() const {
		return operator [](0);
	}

	constexpr inline T &y() {
		return operator [](1);
	}

	constexpr inline const T &y() const {
		return operator [](1);
	}

	constexpr inline T &z() {
		return operator [](2);
	}

	constexpr inline const T &z() const {
		return operator [](2);
	}

	constexpr inline T &w() {
		return operator [](3);
	}

	constexpr inline const T &w() const {
		return operator [](3);
	}

public:
	template<typename = void>
	constexpr inline const Vector<T, 2> xy() const {
		static_assert(D >= 2);
		return Vector<T, 2>(data[0], data[1]);
	}

	template<typename = void>
	constexpr inline const Vector<T, 3> xyz() const {
		static_assert(D >= 3);
		return Vector<T, 3>(data[0], data[1], data[2]);
	}

public:
	T &component(int i) {
		return this->data[i];
	}

	const T &component(int i) const {
		return this->data[i];
	}

	/// Returns a copy of the current vector with component $i set to $set
	V adjustedComponent(int i, T set) {
		V result = *this;
		result.data[i] = set;
		return result;
	}

	constexpr inline T &operator [](int i) {
		ASSERT(i >= 0 && i < D);
		return data[i];
	}

	constexpr inline const T &operator [](int i) const {
		ASSERT(i >= 0 && i < D);
		return data[i];
	}

public:
	template<typename Func>
	inline V componentUnary(Func f) const {
		V result;
		for(int i = 0; i < D; i++)
			result[i] = f(this->data[i]);

		return result;
	}

	template<typename Func>
	inline V componentBinary(const V &o, Func f) const {
		V result;
		for(int i = 0; i < D; i++)
			result[i] = f(this->data[i], o.data[i]);

		return result;
	}

	template<typename Func>
	inline T reduce(Func f) const {
		T result = this->data[0];
		for(int i = 1; i < D; i++)
			result = f(result, this->data[1]);

		return result;
	}

public:
	inline T dotProduct(const V &v) const {
		T result = 0;
		for(int i = 0; i < D; i++)
			result += data[i] * v[i];

		return result;
	}

	inline T length() const {
		return ::sqrt(dotProduct(*this));
	}

	inline T manhattanLength() const {
		T result = 0;
		for(int i = 0; i < D; i++)
			result += ::abs(data[i]);

		return result;
	}

	inline V normalized() const {
		if constexpr(std::is_floating_point_v<T>) {
			const auto len = length();
			const auto lenInv = 1 / len;
			return len ? (*this * lenInv) : V();
		}
		else {
			const auto len = length();
			return len ? (*this / length()) : V();
		}
	}

	inline V abs() const {
		VECTOR_COMPONENT_OP(::abs(data[i]));
	}

	inline V sign() const {
		VECTOR_COMPONENT_OP((T(0) < data[i]) - (data[i] < T(0)));
	}

public:
	inline V floor() const {
		VECTOR_COMPONENT_OP(::floor(data[i]));
	}

	inline V ceil() const {
		VECTOR_COMPONENT_OP(::ceil(data[i]));
	}

	inline V round() const {
		VECTOR_COMPONENT_OP(::round(data[i]));
	}

public:
	constexpr V min(const V &other) const {
		VECTOR_COMPONENT_OP(std::min(data[i], other[i]));
	}

	constexpr V max(const V &other) const {
		VECTOR_COMPONENT_OP(std::max(data[i], other[i]));
	}

	constexpr inline V clamp(const V &minv, const V &maxv) const {
		return this->min(maxv).max(minv);
	}

	int minComponentIndex() const {
		T val = data[0];
		int ix = 0;

		for(int i = 1; i < D; i++) {
			if(data[i] < val) {
				val = data[i];
				ix = i;
			}
		}

		return ix;
	}

	int maxComponentIndex() const {
		T val = data[0];
		int ix = 0;

		for(int i = 1; i < D; i++) {
			if(data[i] > val) {
				val = data[i];
				ix = i;
			}
		}

		return ix;
	}

public:
	template<typename T2>
	Vector<T2, D> componentTernary(const Vector<T2, D> &thn, const Vector<T2, D> &els) const {
		using RT = Vector<T2, D>;
		VECTOR_COMPONENT_OP_RT(RT, this->data[i] ? thn[i] : els[i]);
	}

	template<typename = void>
	bool any() const {
		for(int i = 0; i < D; i++)
			if(this->data[i])
				return true;

		return false;
	}

	template<typename = void>
	bool all() const {
		for(int i = 0; i < D; i++)
			if(!this->data[i])
				return false;

		return true;
	}

public:
	template<typename T2>
	constexpr Vector<T2, D> to() const {
		Vector<T2, D> result;
		for(int i = 0; i < D; i++)
			result[i] = static_cast<T2>(data[i]);

		return result;
	}

public:
	constexpr inline void operator =(const V &other) {
		VECTOR_SELF_COMPONENT_OP(other[i]);
	}

	constexpr inline void operator =(const T &v) {
		VECTOR_SELF_COMPONENT_OP(v);
	}

public:
	constexpr inline V operator ~() const {
		VECTOR_COMPONENT_OP(~data[i]);
	}

	constexpr inline V operator -() const {
		VECTOR_COMPONENT_OP(-data[i]);
	}

#define OP(op) \
  constexpr inline void operator op ## =(const V &v) { VECTOR_SELF_COMPONENT_OP(data[i] op v[i]); } \
  constexpr inline void operator op ## =(const _VectorBase<T, 1> &v) { VECTOR_SELF_COMPONENT_OP(data[i] op v[0]); } \
  constexpr inline void operator op ## =(const T &v) { VECTOR_SELF_COMPONENT_OP(data[i] op v); } \
  \
  constexpr inline V operator op(const V &v) const { VECTOR_COMPONENT_OP(data[i] op v[i]); } \
  constexpr inline V operator op(const _VectorBase<T,1> &v) const { VECTOR_COMPONENT_OP(data[i] op v[0]); } \
  constexpr inline V operator op(const T &v) const { VECTOR_COMPONENT_OP(data[i] op v); }

	OP(+)

	OP(-)

	OP(*)

	OP(/)

	OP(%)

	OP(&)

	OP(|)

#undef OP

public:
	constexpr inline bool operator ==(const V &other) const {
		bool result = true;

		for(int i = 0; i < D; i++)
			result &= (data[i] == other[i]);

		return result;
	}

	constexpr inline bool operator !=(const V &other) const {
		return !(*this == other);
	}

	constexpr inline VB componentEqual(const V &other) const {
		VECTOR_COMPONENT_OP_RT(VB, data[i] == other[i]);
	}

	constexpr inline VB operator >(const V &other) const {
		VECTOR_COMPONENT_OP_RT(VB, data[i] > other[i]);
	}

	constexpr inline VB operator >=(const V &other) const {
		VECTOR_COMPONENT_OP_RT(VB, data[i] >= other[i]);
	}

	constexpr inline VB operator <(const V &other) const {
		VECTOR_COMPONENT_OP_RT(VB, data[i] < other[i]);
	}

	constexpr inline VB operator <=(const V &other) const {
		VECTOR_COMPONENT_OP_RT(VB, data[i] <= other[i]);
	}

public:
	inline V operator &&(const V &other) const {
		VECTOR_COMPONENT_OP(data[i] && other[i]);
	}

	inline V operator ||(const V &other) const {
		VECTOR_COMPONENT_OP(data[i] || other[i]);
	}

public:
	T data[D] = {0};

};

template<typename P>
class _Vector1D : public P {

public:
	using T = typename P::T;
	static constexpr int D = P::D;
	using V = Vector<T, D>;
	using VB = Vector<bool, D>;

public:
	constexpr inline operator T() const {
		return this->data[0];
	}

};

template<typename P>
class _Vector3D : public P {

public:
	using T = typename P::T;
	static constexpr int D = P::D;
	using V = Vector<T, D>;
	using VB = Vector<bool, D>;

public:
	template<typename = void>
	V crossProduct(const V &v) const {
		const T *d = this->data;

		return V(
			d[1] * v[2] - d[2] * v[1],
			d[2] * v[0] - d[0] * v[2],
			d[0] * v[1] - d[1] * v[0]
		);
	}

};

template<typename T, int D>
struct _VectorParent {
	using Base = _VectorBase<T, D>;
	using T1 = Base;
	using T2 = typename std::conditional<D == 1, _Vector1D<T1>, T1>::type;
	using T3 = typename std::conditional<D == 3, _Vector3D<T2>, T2>::type;

	using V = T3;
};

template<typename T_, int D_>
class Vector : public _VectorParent<T_, D_>::V {

public:
	using T = T_;
	static constexpr int D = D_;
	using V = Vector<T, D>;
	using VC = _VectorBase<T_, D_>;
	using VB = Vector<bool, D>;
	static constexpr bool isBoolVector = std::is_same<T, bool>::value;

public:
	constexpr inline Vector() {
		static_assert(sizeof(V) == sizeof(T) * D);
	}

	constexpr inline Vector(const T &v) {
		for(int i = 0; i < D; i++)
			this->data[i] = v;
	}

	constexpr inline Vector(const Vector<T, 1> &v) {
		for(int i = 0; i < D; i++)
			this->data[i] = v.x();
	}

	constexpr inline Vector(const VC &v) {
		for(int i = 0; i < D; i++)
			this->data[i] = v[i];
	}

	template<typename A1, typename A2, typename ...Args>
	constexpr Vector(const A1 &a1, const A2 &a2, Args &&...args) {
		const V v = concatVectors<T>(a1, a2, std::forward<Args>(args)...);
		static_assert(v.D >= D);

		for(int i = 0; i < D; i++)
			this->data[i] = v[i];
	}
};

#define OP(op) \
  template<typename T, int D> constexpr inline Vector<T, D> operator op(const T &l, const Vector<T, D> &r) { VECTOR_COMPONENT_OP(l op r[i]); }

OP(+)

OP(-)

OP(*)

OP(/)

OP(%)

#undef OP

#undef VECTOR_BINARY_OP

template<typename T, int D>
struct std::hash<Vector<T, D>> {
	size_t operator ()(const Vector<T, D> &v) const {
		size_t r = 0;
		const auto h = std::hash<T>{};
		for(const T &c: v.data)
			HashUtils::combineHash(r, h(c));

		return r;
	}
};

template<typename T, int D>
struct std::formatter<Vector<T, D>> : public std::formatter<std::string> {

	auto format(const Vector<T, D> &v, format_context &ctx) {
		return formatter<string>::format(std::format("({})", ::iterator(v.data).mapx(std::format("{}", x)).join(", ")), ctx);
	}
};

template<typename T>
using Vector2 = Vector<T, 2>;
template<typename T>
using Vector3 = Vector<T, 3>;
template<typename T>
using Vector4 = Vector<T, 4>;

using Vector2I = Vector2<int>;
using Vector2I8 = Vector2<int8_t>;
using Vector2I32 = Vector2<int32_t>;
using Vector2UI = Vector2<unsigned int>;
using Vector2U8 = Vector2<uint8_t>;
using Vector2U16 = Vector2<uint16_t>;
using Vector2U32 = Vector2<uint32_t>;
using Vector2F = Vector2<float>;

using Vector3B = Vector3<bool>;
using Vector3I = Vector3<int>;
using Vector3I32 = Vector3<int32_t>;
using Vector3I8 = Vector3<int8_t>;
using Vector3UI = Vector3<unsigned int>;
using Vector3U8 = Vector3<uint8_t>;
using Vector3U16 = Vector3<uint16_t>;
using Vector3U32 = Vector3<uint32_t>;
using Vector3F = Vector3<float>;

using Vector4I = Vector4<int>;
using Vector4I8 = Vector4<int8_t>;
using Vector4I32 = Vector4<int32_t>;
using Vector4UI = Vector4<unsigned int>;
using Vector4U8 = Vector4<uint8_t>;

using Vector4F = Vector4<float>;

using V2I = Vector2I;
using V2F = Vector2F;

using V3U8 = Vector3U8;
using V3F = Vector3F;

using V4F = Vector4F;

/// The vector iterator is inclusive with hi!
template<typename V>
auto vectorIterator(const V &lo, const V &hi, const V &inc = V(1)) {
	using T = typename V::T;
	static constexpr int D = V::D;
	struct E {
	};
	struct I {

	public:
		inline const I &begin() const {
			return *this;
		}

		inline E end() const {
			return {};
		}

	public:
		inline bool operator !=(E) const {
			return c;
		}

		inline const V &operator *() const {
			return pos;
		}

		inline void operator ++() {
			// Message to compiler: please unroll this
			for(int d = 0; d < D; d++) {
				auto &p = pos[d];
				p += inc[d];
				if(p <= hi[d])
					return;

				p = lo[d];
			}

			c = false;
		}

	public:
		V lo, hi, inc, pos;
		bool c = true;

	};

	return I{
		.lo = lo,
		.hi = hi,
		.inc = inc,
		.pos = lo,
		.c = (lo <= hi).all(),
	};
}