#pragma once

#include "util/enumutils.h"
#include "defines.h"

#include "wga_symbol.h"

#define WGA_TYPES(I, A) \
  I(A, Float) I(A, Float2) I(A, Float3) \
  I(A, Bool) /*I(A, Bool2) I(A, Bool3)*/ \
  I(A, Block) \
  I(A, Rule) I(A, ComponentNode) \

class WGA_Value : public WGA_Symbol {

public:
	enum class Dimensionality {
		Unknown,
		DConst,
		DPerChunk, ///< Per chunk
		D2D,
		D3D,
		_count
	};

	enum class ValueType {
#define I(A, name) name,
		WGA_TYPES(I, _)
#undef I

		Undefined
	};

	static constexpr int dimensionalityValueCount[+WGA_Value::Dimensionality::_count] = {1, 1, chunkSurface, chunkVolume};

public:
	static const std::unordered_map<std::string, ValueType> typesByName;
	static const std::unordered_map<ValueType, std::string> typeNames;

public:
	WGA_Value();
	WGA_Value(const WGA_Value &other) = delete;
	virtual ~WGA_Value();

public:
	virtual SymbolType symbolType() const override;

	virtual ValueType valueType() const = 0;

	/// !!! Dimensionality can change depending on the context
	virtual Dimensionality dimensionality() const = 0;

};