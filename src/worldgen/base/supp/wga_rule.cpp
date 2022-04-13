#include "wga_rule.h"

#include "wga_ruleexpansion.h"
#include "wga_component.h"

WGA_Rule::WGA_Rule() {
	setDestription("(rule)");
}

WGA_Symbol::SymbolType WGA_Rule::symbolType() const {
	return SymbolType::Rule;
}

const WGA_Rule::CompiledExpansionList &WGA_Rule::compiledExpansionList() {
	if(compiledReady_)
		return compiledExpansions_;

	QMutexLocker _ml(&compilingMutex_);
	if(compiledReady_)
		return compiledExpansions_;

	for(WGA_RuleExpansion *e: qAsConst(expansions_)) {
		const float priority = e->pragma(QStringLiteral("priority")).toFloat();
		const float probabilityRatio = e->pragma(QStringLiteral("probabilityRatio")).toFloat();

		ASSERT(probabilityRatio > 0);

		const bool allowMirroring = e->component() && e->component()->pragma("allowMirroring").toBool();

		CompiledExpansion ce;
		ce.expansion = e;
		ce.probabilityRatio = probabilityRatio * (allowMirroring ? 0.5 : 1);

		SamePriorityCompiledExpansionList &spl = compiledExpansions_.subLists[priority];
		spl.expansions += ce;

		if(allowMirroring) {
			ce.mirror = true;
			spl.expansions += ce;
		}

		spl.probabilityRatioSum += probabilityRatio;
	}

	compiledReady_ = true;

	return compiledExpansions_;
}

void WGA_Rule::addExpansion(WGA_RuleExpansion *expansion) {
	expansions_ += expansion;
}
