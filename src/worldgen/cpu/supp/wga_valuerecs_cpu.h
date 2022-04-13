#pragma once

#include "worldgen/base/supp/wga_value.h"

using WGA_SymbolID_CPU = uint16_t;

template<WGA_Value::ValueType vt>
struct WGA_ValueRec_CPU;

template<>
struct WGA_ValueRec_CPU<WGA_Value::ValueType::Float> {
	using T = Vector<float, 1>;
};

template<>
struct WGA_ValueRec_CPU<WGA_Value::ValueType::Float2> {
	using T = Vector2F;
};


template<>
struct WGA_ValueRec_CPU<WGA_Value::ValueType::Float3> {
	using T = Vector3F;
};

template<>
struct WGA_ValueRec_CPU<WGA_Value::ValueType::Block> {
	using T = BlockID;
};

template<>
struct WGA_ValueRec_CPU<WGA_Value::ValueType::Bool> {
	using T = bool;
};

template<>
struct WGA_ValueRec_CPU<WGA_Value::ValueType::Rule> {
	using T = WGA_SymbolID_CPU;
};

template<>
struct WGA_ValueRec_CPU<WGA_Value::ValueType::ComponentNode> {
	using T = WGA_SymbolID_CPU;
};
