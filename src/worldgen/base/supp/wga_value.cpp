#include "wga_value.h"

const std::unordered_map<std::string, WGA_Value::ValueType> WGA_Value::typesByName{
#define I(A, name) {#name, WGA_Value::ValueType::name},
	WGA_TYPES(I, _)
#undef I
};

const std::unordered_map<WGA_Value::ValueType, std::string> WGA_Value::typeNames{
#define I(A, name) {WGA_Value::ValueType::name, #name},
	WGA_TYPES(I, _)
#undef I
};

WGA_Value::WGA_Value() {
	setDescription("(value)");
}

WGA_Value::~WGA_Value() {

}

WGA_Symbol::SymbolType WGA_Value::symbolType() const {
	return SymbolType::Value;
}
