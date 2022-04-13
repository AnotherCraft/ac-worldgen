#pragma once

#include <QSharedPointer>

class WGA_DataRecord_CPU {

public:
	using SubKey = uint32_t;
	using Ptr = QSharedPointer<WGA_DataRecord_CPU>;
	struct Key {

	public:
		Key() = default;
		Key(WGA_Symbol *sym, const BlockWorldPos &origin, SubKey subKey);
		Key(const Key &other);

	public:
		WGA_Symbol *symbol = nullptr;
		BlockWorldPos origin;
		SubKey subKey = 0;

	public:
		inline bool operator==(const Key &other) const {
			return symbol == other.symbol && origin == other.origin && subKey == other.subKey;
		}

	};
	using Ctor = std::function<Ptr(const Key &key)>;

public:
	virtual int dataSize() const = 0;

};

inline size_t qHash(const WGA_DataRecord_CPU::Key &key, size_t seed = 0) {
	return qHashMulti(seed, key.symbol, key.origin, key.subKey);
}

template<typename T>
class WGA_DataRecordT_CPU : public WGA_DataRecord_CPU {

public:
	using Ptr = QSharedPointer<WGA_DataRecordT_CPU<T>>;

public:
	T data;

public:
	virtual int dataSize() const override {
		return sizeof(WGA_DataRecordT_CPU<T>);
	};


};

template<typename T>
class WGA_StaticArrayDataRecordBase_CPU : public WGA_DataRecord_CPU {

public:
	T *data;
	int size;

};

template<typename T, int size_>
class WGA_StaticArrayDataRecord_CPU : public WGA_StaticArrayDataRecordBase_CPU<T> {

public:
	WGA_StaticArrayDataRecord_CPU() {
		this->data = data_;
		this->size = size_;
	}

public:
	virtual int dataSize() const override {
		return sizeof(WGA_StaticArrayDataRecord_CPU<T, size_>) * size_;
	};

private:
	T data_[size_];

};
