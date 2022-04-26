#pragma once

#include "../supp/wga_value_cpu.h"
#include "../supp/worldgen_cpu_utils.h"
#include "../supp/wga_valuewrapper_cpu.h"

class WGA_Funcs_CPU {

public:
	using Api = WorldGenAPI_CPU *;
	using Key = const WGA_DataRecord_CPU::Key &;
	using Seed = WorldGenSeed;
	using Dimensionality = WGA_Value::Dimensionality;

	using VT = WGA_Value::ValueType;

	template<VT t>
	using V = WGA_ValueWrapper_CPU<t>;

	template<VT t>
	using DH = WGA_DataHandle_CPU<t>;

public:
	using Func = std::function<WGA_Value *(WorldGenAPI_CPU *api, const WorldGenAPI::FunctionArgs &args)>;
	static std::unordered_map<WorldGenAPI::FunctionID, Func> functions();

};
