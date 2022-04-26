#pragma once

#include <functional>
#include <unordered_map>

#include "util/enumutils.h"

#include "../worldgenapi_cpu.h"
#include "wga_structuregenerator_cpu.h"
#include "wga_datahandle_cpu.h"
#include "wga_datacache_cpu.h"
#include "wga_valuerecs_cpu.h"

class WGA_Value_CPU final : public WGA_Value {

public:
	using DimensionalityFunc = std::function<Dimensionality()>;

public:
	WGA_Value_CPU(WorldGenAPI_CPU &api, ValueType valueType, bool isContextual, const DimensionalityFunc &dimFunc, const WGA_DataRecord_CPU::Ctor &ctor);
	WGA_Value_CPU(WGA_Value_CPU *proxy);

public:
	virtual inline ValueType valueType() const override {
		return valueType_;
	}

	virtual inline Dimensionality dimensionality() const override {
		if(!isContextual_)
			return cachedDimensionality_;

		return !isContextual_ ? cachedDimensionality_ : api_.structureGen->getValueDimensionality(this);
	}

	virtual inline bool isContextual() const override {
		return isContextual_;
	}

	inline bool isCrossSampled(unsigned subKey) const {
		return (crossSampledSubKeys_ >> subKey) & 1;
	}

	inline void markAsCrossSampled(unsigned subKey) {
		crossSampledSubKeys_ |= 1 << subKey;
	}

public:
	inline WorldGenAPI_CPU &api() {
		return api_;
	}

	inline const auto &dimFunc() const {
		return dimFunc_;
	}

	inline const auto &ctor() const {
		return ctor_;
	}

public:
	WGA_DataRecord_CPU::Ptr getDataRecord(const BlockWorldPos &origin, WGA_DataRecord_CPU::SubKey subKey);

private:
	WorldGenAPI_CPU &api_;
	ValueType valueType_;
	bool isContextual_;
	unsigned crossSampledSubKeys_ = 0;

private:
	WGA_Value_CPU *proxy_ = nullptr;
	DimensionalityFunc dimFunc_;
	WGA_DataRecord_CPU::Ctor ctor_;
	Dimensionality cachedDimensionality_ = Dimensionality::_count;

};
