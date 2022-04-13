#include "wga_grammarsymbol.h"


WGA_GrammarSymbol::WGA_GrammarSymbol() {

}

void WGA_GrammarSymbol::setParam(const QString &param, WGA_Value *value) {
	paramSets_ += ParamSet{param, value};
}

void WGA_GrammarSymbol::declareParam(const WGA_GrammarSymbol::ParamDeclare &param) {
	paramDeclares_ += param;
}

void WGA_GrammarSymbol::addCondition(const WGA_GrammarSymbol::Condition &cond) {
	ASSERT(cond.value);
	ASSERT(cond.value->valueType() == WGA_Value::ValueType::Bool);

	conditions_ += cond;
}
