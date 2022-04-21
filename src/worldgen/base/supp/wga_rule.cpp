#include "wga_rule.h"

#include "wga_ruleexpansion.h"
#include "wga_component.h"

WGA_Rule::WGA_Rule() {
	setDescription("(rule)");

	static const PragmaList pg{
		{"depthFirstProbability", 0.0f},
	};
	pragmas_ = pg;
}

WGA_Symbol::SymbolType WGA_Rule::symbolType() const {
	return SymbolType::Rule;
}

const WGA_Rule::CompiledExpansionList &WGA_Rule::compiledExpansionList() {
	if(compiledReady_)
		return compiledExpansions_;

	std::unique_lock _ml(compilingMutex_);
	if(compiledReady_)
		return compiledExpansions_;

	for(WGA_RuleExpansion *e: expansions_) {
		const float priority = std::get<float>(e->pragma("priority"));
		const float probabilityRatio = std::get<float>(e->pragma("probabilityRatio"));

		ASSERT(probabilityRatio > 0);

		const bool allowMirroring = e->component() && std::get<bool>(e->component()->pragma("allowMirroring"));

		CompiledExpansion ce;
		ce.expansion = e;
		ce.probabilityRatio = probabilityRatio * (allowMirroring ? 0.5 : 1);

		SamePriorityCompiledExpansionList &spl = compiledExpansions_.subLists[priority];
		spl.expansions.push_back(ce);

		if(allowMirroring) {
			ce.mirror = true;
			spl.expansions.push_back(ce);
		}

		spl.probabilityRatioSum += probabilityRatio;
	}

	compiledReady_ = true;

	return compiledExpansions_;
}

void WGA_Rule::addExpansion(WGA_RuleExpansion *expansion) {
	expansions_.push_back(expansion);
}
