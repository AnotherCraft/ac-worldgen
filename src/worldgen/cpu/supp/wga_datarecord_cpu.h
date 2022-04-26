#pragma once

#include <functional>

class WGA_DataRecord_CPU {

public:
	using SubKey = uint32_t;
	using Ptr = std::shared_ptr<WGA_DataRecord_CPU>;
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
		inline bool operator ==(const Key &other) const = default;
		
	};
	using Ctor = std::function<Ptr(const Key &key)>;

public:
	virtual int dataSize() const = 0;

};

template<>
struct std::hash<WGA_DataRecord_CPU::Key> {
	inline size_t operator ()(const WGA_DataRecord_CPU::Key &key) const {
		return HashUtils::multiHash(key.symbol, key.origin, key.subKey);
	}
};

template<typename T>
class WGA_DataRecordT_CPU : public WGA_DataRecord_CPU {

public:
	using Ptr = std::shared_ptr<WGA_DataRecordT_CPU<T>>;

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
		return sizeof(T) * size_;
	};

private:
	T data_[size_];

};
