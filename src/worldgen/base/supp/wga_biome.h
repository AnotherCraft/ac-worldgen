#pragma once

#include <unordered_map>
#include <vector>

#include "wga_symbol.h"

class WGA_Biome : public WGA_Symbol {

public:
	struct Condition {
		WGA_Value *param = nullptr;
		float mean = 0, deviation = 0;
	};
	using Conditions = std::vector<Condition>;

public:
	WGA_Biome();

public:
	virtual SymbolType symbolType() const override;

public:
	void addCondition(const Condition &cond);

	inline const Conditions &conditions() const {
		return conditions_;
	}

	/// Returns a value representing biome param (defined by the default value) for the given biome
	inline WGA_Value *param(WGA_Value *param) const {
		if(auto i = params_.find(param); i != params_.end())
			return i->second;

		return param;
	};

	inline const auto &params() const {
		return params_;
	}

	void setParam(WGA_Value *variable, WGA_Value *value);

private:
	Conditions conditions_;
	std::unordered_map<WGA_Value *, WGA_Value *> params_;

};

