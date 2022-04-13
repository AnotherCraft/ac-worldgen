#include "wga_ruleexpansion.h"

#include "wga_rule.h"

WGA_RuleExpansion::WGA_RuleExpansion(WGA_Rule *rule, WGA_Component *component, const QString &node) {
	setDestription("(rule expansion)");

	ASSERT(rule);

	rule_ = rule;
	component_ = component;
	node_ = node;

	static const PragmaList pg{
		{"priority",         1},
		{"probabilityRatio", 100}
	};
	pragmas_ = pg;

	// rule -> false; Has the lowest priority by default
	if(!component_)
		setPragma("priority", 9999);
}

WGA_Symbol::SymbolType WGA_RuleExpansion::symbolType() const {
	return SymbolType::RuleExpansion;
}
