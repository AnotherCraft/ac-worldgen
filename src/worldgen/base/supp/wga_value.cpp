#include "wga_value.h"

const QHash<QString, WGA_Value::ValueType> WGA_Value::typesByName{
#define I(A, name) {#name, WGA_Value::ValueType::name},
	WGA_TYPES(I, _)
#undef I
};

const QHash<WGA_Value::ValueType, QString> WGA_Value::typeNames{
#define I(A, name) {WGA_Value::ValueType::name, #name},
	WGA_TYPES(I, _)
#undef I
};

WGA_Value::WGA_Value() {
	setDestription("(value)");
}

WGA_Value::~WGA_Value() {

}

WGA_Symbol::SymbolType WGA_Value::symbolType() const {
	return SymbolType::Value;
}
