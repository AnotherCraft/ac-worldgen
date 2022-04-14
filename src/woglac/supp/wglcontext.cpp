#include "wglcontext.h"

#include "util/iterators.h"

#include "wglerror.h"

WGLContext::WGLContext() {
	clear();
}

WGLContext::~WGLContext() {
	clear();
}

void WGLContext::clear() {
	for(auto *s: allSymbols)
		delete s;

	astSymbolMapping.clear();
	allSymbols.clear();

	unresolvedApiCmds_.clear();
	resolvedApiCmds_.clear();
	definedSymbols_.clear();
	symbolApiCmdDependents_.clear();

	rootSymbol = new WGLSymbol(this, nullptr, QString(), WGLSymbol::Type::Namespace, nullptr);
}

void WGLContext::addApiCmd(WGLSymbol *definingSymbol, const DependencyList &dependencies, const WGLContext::APICommand &cmd) {
	ASSERT(!definedSymbols_.contains(definingSymbol));

	int unresolvedCount = 0;

	for(WGLSymbol *s: dependencies) {
		if(s && !definedSymbols_.contains(s))
			unresolvedCount++;
	}

	if(!unresolvedCount) {
		resolvedApiCmds_ += cmd;
		if(definingSymbol)
			markSymbolDefined(definingSymbol);

		return;
	}

	const int id = unresolvedApiCmds_.size();
	unresolvedApiCmds_ += UnresolvedAPICmd{cmd, definingSymbol, unresolvedCount};

	for(WGLSymbol *s: dependencies) {
		if(s && !definedSymbols_.contains(s))
			symbolApiCmdDependents_.insert(s, id);
	}
}

void WGLContext::checkCircularDependencies() {
	if(symbolApiCmdDependents_.empty())
		return;

	QStringList err{
		QStringLiteral("Circular dependencies detected. Relevant symbols:")
	};

	for(auto it = symbolApiCmdDependents_.begin(); it != symbolApiCmdDependents_.end(); it++) {
		WGLSymbol *l = it.key(), *r = unresolvedApiCmds_[it.value()].definingSymbol;
		const QString line = r ? QString::number(r->declarationAst_->getStart()->getLine()) : QString();

		err += QStringLiteral("[%1] %2 -> %3").arg(line, r ? r->fullName() : "??", l ? l->fullName() : "??");
	}

	throw WGLError(err.join('\n'), nullptr);
}

void WGLContext::markSymbolDefined(WGLSymbol *s) {
	definedSymbols_ += s;

	QVector<WGLSymbol *> newlyDefinedSymbols;

	for(auto it = symbolApiCmdDependents_.find(s); it != symbolApiCmdDependents_.end() && it.key() == s; it++) {
		UnresolvedAPICmd &rec = unresolvedApiCmds_[*it];
		ASSERT(rec.unresolvedDependencyCount > 0);

		rec.unresolvedDependencyCount--;
		if(!rec.unresolvedDependencyCount) {
			resolvedApiCmds_ += rec.command;
			if(rec.definingSymbol)
				newlyDefinedSymbols += rec.definingSymbol;
		}
	}

	symbolApiCmdDependents_.remove(s);

	for(WGLSymbol *s: newlyDefinedSymbols)
		markSymbolDefined(s);
}
