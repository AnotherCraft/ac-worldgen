#pragma once

#include "wga_grammarsymbol.h"

class WGA_RuleExpansion : public WGA_GrammarSymbol {

public:
	WGA_RuleExpansion(WGA_Rule *rule, WGA_Component *component, const QString &node);

public:
	virtual SymbolType symbolType() const override;

public:
	inline WGA_Component *component() {
		return component_;
	}

	inline const QString &node() {
		return node_;
	}

private:
	WGA_Rule *rule_;
	WGA_Component *component_ = nullptr;
	QString node_;

};

