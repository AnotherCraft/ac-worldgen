#include "wga_biome.h"
#include "wga_value.h"

WGA_Biome::WGA_Biome() {
	setDestription("(biome)");
}

WGA_Symbol::SymbolType WGA_Biome::symbolType() const {
	return SymbolType::Biome;
}

void WGA_Biome::addCondition(const WGA_Biome::Condition &cond) {
	conditions_ += cond;
}

void WGA_Biome::setParam(WGA_Value *variable, WGA_Value *value) {
	ASSERT(variable->valueType() == value->valueType());
	ASSERT(!params_.contains(variable));

	params_[variable] = value;
}
