#pragma once

#include <vector>
#include <mutex>

#include "util/enumutils.h"
#include "util/tracyutils.h"

#include "wga_value_cpu.h"
#include "wga_datahandle_cpu.h"

template<WGA_Value::ValueType t>
using WGA_FillFunc = std::function<void(const WGA_DataRecord_CPU::Key &key, const WGA_DataHandle_CPU<t> &result)>;


template<WGA_Value::ValueType t, int d>
WGA_DataCache_CPU::DataRecordPtr wga_dimFillCtor(const WGA_DataRecord_CPU::Key &key, const WGA_FillFunc<t> &fillFunc) {
	using T = typename WGA_ValueRec_CPU<t>::T;
	constexpr int cnt = WGA_Value::dimensionalityValueCount[d];
	using DataRecord = WGA_StaticArrayDataRecord_CPU<T, cnt>;
	using DataHandle = WGA_DataHandle_CPU<t>;

	static std::vector<DataRecord *> recycleList_;
	static std::mutex recycleMutex_;

	static const auto dtor = [](DataRecord *rec) {
		std::unique_lock _ml(recycleMutex_);
		if(recycleList_.size() > 1024)
			delete rec;
		else
			recycleList_.push_back(rec);
	};

	DataRecord *rec = nullptr;
	{
		std::unique_lock _ml(recycleMutex_);
		if(!recycleList_.empty()) {
			rec = recycleList_.back();
			recycleList_.pop_back();
		}
	}

	if(!rec)
		rec = new DataRecord();
	else
		rec = new(rec) DataRecord();

	const std::shared_ptr<WGA_DataRecord_CPU> recPtr(rec, dtor);

	DataHandle handle{recPtr, rec->data, cnt, cnt - 1};

	{
		fillFunc(key, handle);
	}

	return recPtr;
}


template<WGA_Value::ValueType t>
WGA_DataRecord_CPU::Ctor wga_fillCtor(const WGA_Value_CPU::DimensionalityFunc &dimFunc, const WGA_FillFunc<t> &fillFunc, const char *funcName) {
	static const auto dimFillFs = std::vector<std::function<WGA_DataCache_CPU::DataRecordPtr(const WGA_DataRecord_CPU::Key &, const WGA_FillFunc<t> &)> >{
		/* Unknown dimensionality */ &wga_dimFillCtor<t, 0>, &wga_dimFillCtor<t, 0>, &wga_dimFillCtor<t, 1>, &wga_dimFillCtor<t, 2>, &wga_dimFillCtor<t, 3>
	};
	ASSERT(dimFillFs.size() == +WGA_Value::Dimensionality::_count);

	return [fillFunc, dimFunc, funcName](const WGA_DataRecord_CPU::Key &key) {
		// Tracy worldgen profiling
		ZoneTransientN(tracyZone, funcName, true);

		const WGA_Value::Dimensionality dim = dimFunc();
		return dimFillFs[+dim](key, fillFunc);
	};
}
