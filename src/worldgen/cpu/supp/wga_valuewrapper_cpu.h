#pragma once

#include "util/quickcache.h"

#include "wga_value_cpu.h"

template<WGA_Value::ValueType type>
struct WGA_ValueWrapper_CPU {

public:
	using T = typename WGA_ValueRec_CPU<type>::T;
	using DataHandle = WGA_DataHandle_CPU<type>;
	static constexpr WGA_Value::ValueType valueType = type;

public:
	WGA_ValueWrapper_CPU(WGA_Value_CPU *v)
		: v(v) {
		if(v) {
			ASSERT(v->valueType() == type);
		}
	}

	WGA_ValueWrapper_CPU(WGA_Value *v)
		: WGA_ValueWrapper_CPU(v ? static_cast<WGA_Value_CPU *>(v) : nullptr) {

	}

public:
	WGA_Value::Dimensionality dimensionality() const {
		return v->dimensionality();
	}

public:
	inline const DataHandle &dataHandle(const BlockWorldPos &origin, WGA_DataRecord_CPU::SubKey subKey = 0) {
		if(handleCache_.isAndSet(origin))
			return cachedHandle_;

		using Rec = WGA_StaticArrayDataRecordBase_CPU<T>;

		WGA_DataRecord_CPU::Ptr rec = v->getDataRecord(origin, subKey);
		Rec *rp = static_cast<Rec *>(rec.data());

		cachedHandle_.data = rp->data;
		cachedHandle_.handle = rec;
		cachedHandle_.size = rp->size;
		cachedHandle_.flag = cachedHandle_.size - 1;

		return cachedHandle_;
	}

	inline auto constValue(WGA_DataRecord_CPU::SubKey subKey = 0) {
		return dataHandle(BlockWorldPos(), subKey)[0];
	}

	inline auto chunkValue(const ChunkWorldPos &pos, WGA_DataRecord_CPU::SubKey subKey = 0) {
		return dataHandle(BlockWorldPos::fromChunkBlockIndex(pos, 0, 0), subKey)[0];
	}

	inline auto sampleAt(const BlockWorldPos &pos, WGA_DataRecord_CPU::SubKey subKey = 0) {
		return dataHandle(pos & ~(chunkSize - 1), subKey)[pos];
	}

public:
	WGA_Value_CPU *v = nullptr;

private:
	QuickCache<BlockWorldPos> handleCache_;
	DataHandle cachedHandle_;

};
