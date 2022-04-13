#pragma once

#include "pch.h"
#include "util/blockorientation.h"

#include "wga_grammarsymbol.h"

/// Nodes are used for connecting the structures using rules and rule expansions
/// Nodes are expanded only after the whole construct is drafted
class WGA_ComponentNode : public WGA_Symbol {

public:
	struct Config {
		QString group;
		WGA_Value *position = nullptr;
		WGA_Rule *rule = nullptr; ///< Can be null
		BlockOrientation orientation;
	};

public:
	WGA_ComponentNode();

public:
	virtual SymbolType symbolType() const override;

	inline const Config &config() const {
		return config_;
	}

	void setConfig(const Config &set);

	inline WGA_Component *parentComponent() {
		return parentComponent_;
	}

	void setParentComponent(WGA_Component *set);

private:
	Config config_;
	WGA_Component *parentComponent_ = nullptr;

};

