#pragma once

#include "wga_grammarsymbol.h"

class WGA_RuleExpansion : public WGA_GrammarSymbol {

public:
	WGA_RuleExpansion(WGA_Rule *rule);
	WGA_RuleExpansion(WGA_Rule *rule, WGA_Component *component, const std::string &node);
	WGA_RuleExpansion(WGA_Rule *rule, WGA_Rule *targetRule);

public:
	virtual SymbolType symbolType() const override;

public:
	inline WGA_Component *component() {
		return component_;
	}

	inline const std::string &node() {
		return node_;
	}

	inline WGA_Rule *targetRule() {
		return targetRule_;
	}

private:
	WGA_Rule *rule_;
	WGA_Component *component_ = nullptr;
	WGA_Rule *targetRule_ = nullptr;
	std::string node_;

};

