#pragma once

template<size_t bitCount_, typename BitIndex_ = size_t, typename T_ = void>
struct BitSet {

public:
	static constexpr size_t bitCount = bitCount_;
	static constexpr size_t byteCount = (bitCount + 7) / 8;

	using _T3 = std::conditional_t<byteCount <= sizeof(unsigned long), unsigned long, unsigned long long>;
	using _T2 = std::conditional_t<byteCount <= sizeof(unsigned int), unsigned int, _T3>;
	using T = std::conditional_t<!std::is_same_v<T_, void>, T_, _T2>;

	static constexpr size_t bitsPerElem = sizeof(T) * 8;
	static constexpr size_t arraySize = (bitCount + bitsPerElem - 1) / bitsPerElem;

	using BitIndex = BitIndex_;

public:
	BitSet() = default;
	BitSet(const BitSet &o) = default;

	explicit BitSet(T v) {
		data[0] = v;
	}

public:
	/// Returns count of set bits
	BitIndex count() const {
		BitIndex r = 0;
		for(const uint8_t *i = byteData(), *end = i + byteCount; i != end; i++)
			r += setBitCount_[*i];

		return r;
	}

	bool isEmpty() const {
		for(auto *i = data, *e = data + arraySize; i != e; i++)
			if(*i)
				return false;

		return true;
	}

public:
	inline BitSet &setBit(BitIndex bit) {
		const BitIndex arri = bit / bitsPerElem;
		const T mask = static_cast<T>(1) << (bit - arri * bitsPerElem);
		data[arri] |= mask;
		return *this;
	}

	inline BitSet &unsetBit(BitIndex bit) {
		const BitIndex arri = bit / bitsPerElem;
		const T mask = static_cast<T>(1) << (bit - arri * bitsPerElem);
		data[arri] &= ~mask;
		return *this;
	}

	inline bool testAndUnsetBit(BitIndex bit) {
		const BitIndex arri = bit / bitsPerElem;
		const T mask = static_cast<T>(1) << (bit - arri * bitsPerElem);
		const bool r = data[arri] & mask;
		data[arri] &= ~mask;
		return r;
	}

	inline BitSet &setBit(BitIndex bit, bool set) {
		const BitIndex arri = bit / bitsPerElem;
		const T mask = static_cast<T>(1) << (bit - arri * bitsPerElem);

		if(set)
			data[arri] |= mask;
		else
			data[arri] &= ~mask;

		return *this;
	}

	inline bool testBit(BitIndex bit) const {
		const BitIndex arri = bit / bitsPerElem;
		const T mask = static_cast<T>(1) << (bit - arri * bitsPerElem);
		return data[arri] & mask;
	}

public:
	/// Returns index of first set bit or -1 on failure
	BitIndex firstSetBit() const {
		for(const uint8_t *i = byteData(), *end = i + byteCount; i != end; i++) {
			if(const auto sb = firstSetBit_[*i]; sb != 8)
				return static_cast<BitIndex>((i - byteData()) * 8 + sb);
		}

		return static_cast<BitIndex>(-1);
	}

	/// Returns index of first set bit (beginning the test from start) or -1 on failure
	BitIndex nextSetBit(BitIndex lastTestedBit) const {
		auto start = lastTestedBit + 1;
		const uint8_t *i = byteData() + start / 8;
		const uint8_t *end = byteData() + byteCount;
		if(i >= end)
			return static_cast<BitIndex>(-1);

		{
			const uint8_t mask = 0xf << (start % 8);
			if(const auto sb = firstSetBit_[(*i) & mask]; sb != 8)
				return static_cast<BitIndex>((i - byteData()) * 8 + sb);

			i++;
		}

		for(; i < end; i++) {
			if(const auto sb = firstSetBit_[*i]; sb != 8)
				return static_cast<BitIndex>((i - byteData()) * 8 + sb);
		}

		return static_cast<BitIndex>(-1);
	}

	/// Returns index of nth set bit or -1 on failure
	BitIndex nthSetBit(BitIndex n) const {
		for(const uint8_t *i = byteData(), *end = i + byteCount; i != end; i++) {
			for(int j = 0; j < 8; j++) {
				// TODO: faster
				if(((*i) & (1 << j)) && (n-- <= 0))
					return (i - byteData()) * 8 + j;
			}
		}

		return static_cast<BitIndex>(-1);
	}

	/// Returns index of nth set bit (or -1 on failure) and unsets the bit
	BitIndex takeNthSetBit(BitIndex n) {
		BitIndex i = nthSetBit(n);
		if(i != static_cast<BitIndex>(-1))
			setBit(i, false);

		return i;
	}

public:
	const uint8_t *byteData() const {
		return reinterpret_cast<const uint8_t *>(data);
	}

public:
	BitSet operator &(T mask) const {
		BitSet r;
		r.data[0] = data[0] & mask;
		return r;
	}

public:
	inline BitSet &operator |=(const T v) {
		data[0] |= v;
		return *this;
	}

public:
	inline BitSet &operator |=(const BitSet &o) {
		for(int i = 0; i < arraySize; i++)
			data[i] |= o.data[i];
		return *this;
	}

public:
	struct Iterator {
		const BitSet &bs;
		BitIndex ix;
	};

public:
	T data[arraySize] = {};

private:
	static inline const char *const setBitCount_ =
		"\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
		"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
		"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
		"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7\4\5\5\6\5\6\6\7\5\6\6\7\6\7\7\x8";

	static inline const char *const firstSetBit_ =
		"\x8\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0"
		"\5\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0"
		"\6\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0"
		"\5\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0"
		"\7\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0"
		"\5\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0"
		"\6\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0"
		"\5\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0";

};