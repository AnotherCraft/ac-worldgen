#pragma once

#include <QMutex>

#include "wga_grammarsymbol.h"

class WGA_Rule : public WGA_GrammarSymbol {

public:
	struct CompiledExpansion {
		WGA_RuleExpansion *expansion;
		float probabilityRatio;
		bool mirror = false;
	};
	struct SamePriorityCompiledExpansionList {
		QVector<CompiledExpansion> expansions;
		float probabilityRatioSum = 0;
	};
	struct CompiledExpansionList {
		/// Expansions are grouped by priority into lists.
		QMap<float, SamePriorityCompiledExpansionList> subLists;
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
	QList<WGA_RuleExpansion *> expansions_;
	CompiledExpansionList compiledExpansions_;
	bool compiledReady_ = false;
	QMutex compilingMutex_;

};

