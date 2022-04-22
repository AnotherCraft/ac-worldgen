#include "wga_ruleexpansion.h"

#include <iostream>

#include "wga_rule.h"

WGA_RuleExpansion::WGA_RuleExpansion(WGA_Rule *rule) {
	setDescription("(rule expansion)");

	ASSERT(rule);

	rule_ = rule;
	static const PragmaList pg{
		{"priority",         1.0f},
		{"probabilityRatio", 100.0f}
	};
	pragmas_ = pg;

	// rule -> false; Has the lowest priority by default
	if(!component_ && !targetRule_)
		setPragma("priority", 9999.0f);
}

WGA_RuleExpansion::WGA_RuleExpansion(WGA_Rule *rule, WGA_Component *component, const std::string &node) : WGA_RuleExpansion(rule) {
	component_ = component;
	node_ = node;
	targetType_ = TargetType::expandsToComponent;
}

WGA_RuleExpansion::WGA_RuleExpansion(WGA_Rule *rule, WGA_Rule *targetRule) : WGA_RuleExpansion(rule) {
	targetRule_ = targetRule;
	targetType_ = TargetType::expandsToRule;
}

WGA_Symbol::SymbolType WGA_RuleExpansion::symbolType() const {
	return SymbolType::RuleExpansion;
}
