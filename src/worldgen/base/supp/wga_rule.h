#pragma once

#include <unordered_map>
#include <vector>
#include <mutex>

#include "pch.h"
#include "wga_grammarsymbol.h"

class WGA_Rule : public WGA_GrammarSymbol {

public:
	struct CompiledExpansion {
		WGA_RuleExpansion *expansion;
		float probabilityRatio;
		bool mirror = false;
	};
	struct SamePriorityCompiledExpansionList {
		std::vector<CompiledExpansion> expansions;
		float probabilityRatioSum = 0;
	};
	struct CompiledExpansionList {
		/// Expansions are grouped by priority into lists.
		std::unordered_map<float, SamePriorityCompiledExpansionList> subLists;
	};

public:
	WGA_Rule();

public:
	virtual SymbolType symbolType() const override;

public:
	inline const auto &expansions() const {
		return expansions_;
	}

	const CompiledExpansionList &compiledExpansionList();
	void addExpansion(WGA_RuleExpansion *expansion);

private:
	std::vector<WGA_RuleExpansion *> expansions_;
	CompiledExpansionList compiledExpansions_;
	bool compiledReady_ = false;
	std::mutex compilingMutex_;

};

