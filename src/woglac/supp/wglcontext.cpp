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

	rootSymbol = new WGLSymbol(this, nullptr, {}, WGLSymbol::Type::Namespace, nullptr);
}

void WGLContext::addApiCmd(WGLSymbol *definingSymbol, const DependencyList &dependencies, const WGLContext::APICommand &cmd) {
	ASSERT(!definedSymbols_.contains(definingSymbol));

	int unresolvedCount = 0;

	for(WGLSymbol *s: dependencies) {
		if(s && !definedSymbols_.contains(s))
			unresolvedCount++;
	}

	if(!unresolvedCount) {
		resolvedApiCmds_.push_back(cmd);
		if(definingSymbol)
			markSymbolDefined(definingSymbol);

		return;
	}

	const int id = unresolvedApiCmds_.size();
	unresolvedApiCmds_.push_back(UnresolvedAPICmd{cmd, definingSymbol, unresolvedCount});

	for(WGLSymbol *s: dependencies) {
		if(s && !definedSymbols_.contains(s))
			symbolApiCmdDependents_.insert({s, id});
	}
}

void WGLContext::checkCircularDependencies() {
	if(symbolApiCmdDependents_.empty())
		return;

	std::vector<std::string> err{"Circular dependencies detected. Relevant symbols:"};

	for(auto it = symbolApiCmdDependents_.begin(); it != symbolApiCmdDependents_.end(); it++) {
		WGLSymbol *l = it->first, *r = unresolvedApiCmds_[it->second].definingSymbol;
		const std::string line = r ? std::to_string(r->declarationAst_->getStart()->getLine()) : std::string{};

		err.push_back(std::format("[{}] {} -> {}", line, r ? r->fullName() : "??", l ? l->fullName() : "??"));
	}

	throw WGLError(iterator(err).join('\n'), nullptr);
}

void WGLContext::markSymbolDefined(WGLSymbol *s) {
	definedSymbols_.insert(s);

	QVector<WGLSymbol *> newlyDefinedSymbols;

	for(auto it = symbolApiCmdDependents_.find(s); it != symbolApiCmdDependents_.end() && it->first == s; it++) {
		UnresolvedAPICmd &rec = unresolvedApiCmds_[it->second];
		ASSERT(rec.unresolvedDependencyCount > 0);

		rec.unresolvedDependencyCount--;
		if(!rec.unresolvedDependencyCount) {
			resolvedApiCmds_.push_back(rec.command);
			if(rec.definingSymbol)
				newlyDefinedSymbols += rec.definingSymbol;
		}
	}

	symbolApiCmdDependents_.erase(s);

	for(WGLSymbol *s: newlyDefinedSymbols)
		markSymbolDefined(s);
}
