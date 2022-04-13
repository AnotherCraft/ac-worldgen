#pragma once

#include <type_traits>
#include <array>

#include <QHash>

#include "vector.h"

template<typename T, int W, int H>
struct Matrix;

template<typename T_, int W_, int H_>
struct _MatrixBase {

public:
	using T = T_;
	static constexpr int W = W_;
	static constexpr int H = H_;
	using M = Matrix<T, W, H>;

public:
	_MatrixBase() {
		for(int y = 0; y < H; y++) {
			for(int x = 0; x < W; x++) {
				data[y][x] = (x == y);
			}
		}
	}

public:
	template<int D = H>
	void setColumn(int col, const Vector<T, D> &v) {
		for(int i = 0; i < D; i++)
			data[i][col] = v[i];
	}

	template<int D = W>
	void setRow(int row, const Vector<T, D> &v) {
		for(int i = 0; i < D; i++)
			data[row][i] = v[i];
	}

public:
	inline void operator=(const M &m) {
		data = m.data;
	}

	bool operator==(const M &m) const {
		bool result = true;

		for(int y = 0; y < H; y++) {
			for(int x = 0; x < W; x++)
				result &= (data[y][x] == m.data[y][x]);
		}

		return result;
	}

	inline bool operator!=(const M &m) const {
		return !(*this == m);
	}

	template<int W2>
	Matrix<T, W2, H> operator*(const Matrix<T, W2, W> &m) const {
		Matrix<T, W2, H> result;

		for(int y = 0; y < H; y++) {
			for(int x = 0; x < W2; x++) {
				T v = 0;

				for(int i = 0; i < W; i++)
					v += data[y][i] * m.data[i][x];

				result.data[y][x] = v;
			}
		}

		return result;
	}

	inline T &operator()(int x, int y) {
		ASSERT(x >= 0 && x < W);
		ASSERT(y >= 0 && y < H);
		return data[y][x];
	}

	inline const T &operator()(int x, int y) const {
		ASSERT(x >= 0 && x < W);
		ASSERT(y >= 0 && y < H);
		return data[y][x];
	}

public:
	T data[H][W];

};

template<typename P>
struct _MatrixSquare : public P {

public:
	static constexpr int W = P::W;

	using T = typename P::T;
	using M = typename P::M;

	using V = Vector<T, W>;
	using VA = Vector<T, W - 1>;


public:
	static M translation(const VA &v) {
		M result;

		for(int i = 0; i < W - 1; i++)
			result.data[i][W - 1] = v[i];

		return result;
	}

	static M scaling(const VA &v) {
		M result;

		for(int i = 0; i < W - 1; i++)
			result.data[i][i] = v[i];

		return result;
	}

public:
	M nonScalingInverted() const {
		M result;

		const T *d = &this->data[0][0];
		T *i = &result.data[0][0];

		i[0] =
			d[5] * d[10] * d[15] - d[5] * d[11] * d[14] - d[9] * d[6] * d[15] + d[9] * d[7] * d[14] + d[13] * d[6] * d[11] -
			d[13] * d[7] * d[10];
		i[4] =
			-d[4] * d[10] * d[15] + d[4] * d[11] * d[14] + d[8] * d[6] * d[15] - d[8] * d[7] * d[14] - d[12] * d[6] * d[11] +
			d[12] * d[7] * d[10];
		i[8] =
			d[4] * d[9] * d[15] - d[4] * d[11] * d[13] - d[8] * d[5] * d[15] + d[8] * d[7] * d[13] + d[12] * d[5] * d[11] -
			d[12] * d[7] * d[9];
		i[12] =
			-d[4] * d[9] * d[14] + d[4] * d[10] * d[13] + d[8] * d[5] * d[14] - d[8] * d[6] * d[13] - d[12] * d[5] * d[10] +
			d[12] * d[6] * d[9];
		i[1] =
			-d[1] * d[10] * d[15] + d[1] * d[11] * d[14] + d[9] * d[2] * d[15] - d[9] * d[3] * d[14] - d[13] * d[2] * d[11] +
			d[13] * d[3] * d[10];
		i[5] =
			d[0] * d[10] * d[15] - d[0] * d[11] * d[14] - d[8] * d[2] * d[15] + d[8] * d[3] * d[14] + d[12] * d[2] * d[11] -
			d[12] * d[3] * d[10];
		i[9] =
			-d[0] * d[9] * d[15] + d[0] * d[11] * d[13] + d[8] * d[1] * d[15] - d[8] * d[3] * d[13] - d[12] * d[1] * d[11] +
			d[12] * d[3] * d[9];
		i[13] =
			d[0] * d[9] * d[14] - d[0] * d[10] * d[13] - d[8] * d[1] * d[14] + d[8] * d[2] * d[13] + d[12] * d[1] * d[10] -
			d[12] * d[2] * d[9];
		i[2] = d[1] * d[6] * d[15] - d[1] * d[7] * d[14] - d[5] * d[2] * d[15] + d[5] * d[3] * d[14] + d[13] * d[2] * d[7] -
		       d[13] * d[3] * d[6];
		i[6] =
			-d[0] * d[6] * d[15] + d[0] * d[7] * d[14] + d[4] * d[2] * d[15] - d[4] * d[3] * d[14] - d[12] * d[2] * d[7] +
			d[12] * d[3] * d[6];
		i[10] =
			d[0] * d[5] * d[15] - d[0] * d[7] * d[13] - d[4] * d[1] * d[15] + d[4] * d[3] * d[13] + d[12] * d[1] * d[7] -
			d[12] * d[3] * d[5];
		i[14] =
			-d[0] * d[5] * d[14] + d[0] * d[6] * d[13] + d[4] * d[1] * d[14] - d[4] * d[2] * d[13] - d[12] * d[1] * d[6] +
			d[12] * d[2] * d[5];
		i[3] = -d[1] * d[6] * d[11] + d[1] * d[7] * d[10] + d[5] * d[2] * d[11] - d[5] * d[3] * d[10] - d[9] * d[2] * d[7] +
		       d[9] * d[3] * d[6];
		i[7] = d[0] * d[6] * d[11] - d[0] * d[7] * d[10] - d[4] * d[2] * d[11] + d[4] * d[3] * d[10] + d[8] * d[2] * d[7] -
		       d[8] * d[3] * d[6];
		i[11] = -d[0] * d[5] * d[11] + d[0] * d[7] * d[9] + d[4] * d[1] * d[11] - d[4] * d[3] * d[9] - d[8] * d[1] * d[7] +
		        d[8] * d[3] * d[5];
		i[15] = d[0] * d[5] * d[10] - d[0] * d[6] * d[9] - d[4] * d[1] * d[10] + d[4] * d[2] * d[9] + d[8] * d[1] * d[6] -
		        d[8] * d[2] * d[5];

		T det = d[0] * i[0] + d[1] * i[4] + d[2] * i[8] + d[3] * i[12];
		ASSERT(det == 1);

		return result;
	}

public:
	using P::operator*;

	V operator*(const V &v) const {
		V result;
		for(int y = 0; y < W; y++) {
			for(int x = 0; x < W; x++) {
				result[y] += this->data[y][x] * v[x];
			}
		}

		return result;
	}

	VA operator*(const VA &v) const {
		V result = *this * V(v, 1);

		if(result[W - 1] != 1)
			result /= result[W - 1];

		VA resultA;
		for(int i = 0; i < W - 1; i++)
			resultA[i] = result[i];

		return resultA;
	}

	inline void operator*=(const M &m) {
		*this = *this * m;
	}

};


template<typename P>
struct _Matrix4x4 : public P {

public:
	using T = typename P::T;
	using M = typename P::M;
	using VA = typename P::VA;

public:
	/// Expects all vectors to be normalized
	static M lookAt(const VA &eye, const VA &center, const VA &up) {
		const VA forward = center - eye;
		ASSERT(forward != 0);

		const VA side = forward.crossProduct(up);
		const VA upn = side.crossProduct(forward);

		M m;
		m.setRow(0, side);
		m.setRow(1, upn);
		m.setRow(2, -forward);

		return m;
	}

};

template<typename T, int W, int H>
struct _MatrixParent {
	using M1 = _MatrixBase<T, W, H>;
	using M2 = typename std::conditional<W == H, _MatrixSquare<M1>, M1>::type;
	using M3 = typename std::conditional<W == 4 && H == 4, _Matrix4x4<M2>, M2>::type;

	using M = M3;
};

template<typename T, int W, int H>
struct Matrix : public _MatrixParent<T, W, H>::M {

public:
	Matrix() {

	}

	/// Row major order
	Matrix(const std::array<T, W * H> &v) {
		for(int i = 0; i < v.size(); i++)
			this->data[i / W][i % W] = v[i];
	}

};

template<typename T, int W, int H>
size_t qHash(const Matrix<T, W, H> &m, size_t seed = 0) {
	for(int y = 0; y < H; y++) {
		for(int x = 0; x < W; x++) {
			seed = qHash(m.data[y][x], seed);
		}
	}

	return seed;
};
