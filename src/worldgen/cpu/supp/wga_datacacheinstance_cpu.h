#pragma once

#include "util/bytesizeliterals.h"
#include "util/randomaccesshashtable.h"

#include "wga_datarecord_cpu.h"

class WGA_DataCacheInstance_CPU {

public:
	using Key = WGA_DataRecord_CPU::Key;
	using Value = QSharedPointer<WGA_DataRecord_CPU>;

public:
	inline size_t memoryCapacity() const {
		return memoryCapacity_;
	}

	inline void setMemoryCapacity(size_t set) {
		memoryCapacity_ = set;
	}

public:
	Value get(const Key &key);

	void insert(const Key &key, const Value &value, size_t memorySize);

private:
	/// Maximum occupied memory by the records
	size_t memoryCapacity_ = 1_MB;
	size_t usedMemory_ = 0;

	/// Increases with each read access
	size_t accessCounter_ = 0;

private:
	struct Record {
		Value value;
		size_t memorySize = 0;

		/// Value of accessCounter during the last read
		size_t lastAccess = 0;

	};
	/// Temporary implementation
	RandomAccessHashTable<Key, Record> hash_;

};

