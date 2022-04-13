#pragma once

#include <QHash>
#include <QString>

#include "util/enumutils.h"
#include "defines.h"

#include "wga_symbol.h"

#define WGA_TYPES(I, A) \
  I(A, Float) I(A, Float2) I(A, Float3) \
  I(A, Bool) /*I(A, Bool2) I(A, Bool3)*/ \
  I(A, Block) \
  I(A, Rule) I(A, ComponentNode) \

class WGA_Value : public WGA_Symbol {
Q_GADGET

public:
	enum class Dimensionality {
		Unknown,
		DConst,
		DPerChunk, ///< Per chunk
		D2D,
		D3D,
		_count
	};

	Q_ENUM(Dimensionality);

	enum class ValueType {
#define I(A, name) name,
		WGA_TYPES(I, _)
#undef I

		Undefined
	};

	Q_ENUM(ValueType);

	static constexpr int dimensionalityValueCount[+WGA_Value::Dimensionality::_count] = {1, 1, chunkSurface, chunkVolume};

public:
	static const QHash<QString, ValueType> typesByName;
	static const QHash<ValueType, QString> typeNames;

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


inline size_t qHash(WGA_Value::ValueType t, size_t seed = 0) {
	return qHash(static_cast<int>(t), seed);
}
