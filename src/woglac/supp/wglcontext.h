#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>

// Must place before everything else because of antlr
#include "wglinclude.h"

#include "wglsymbol.h"
#include "wglapicontext.h"

class WGLContext {

public:
	using APICommand = std::function<void(WGLAPIContext &)>;
	using DependencyList = std::unordered_set<WGLSymbol *>;

public:
	WGLContext();
	~WGLContext();

	void clear();

public:
	WGLCompiler *compiler;
	WGLSymbol *rootSymbol;
	QList<WGLSymbol *> allSymbols;

	/// Associates symbols with AST contexts; filled in declaration pass
	QHash<antlr4::ParserRuleContext *, WGLSymbol *> astSymbolMapping;

public:
	void addApiCmd(WGLSymbol *definingSymbol, const DependencyList &dependencies, const APICommand &cmd);
	void checkCircularDependencies();

	inline const auto &apiCommands() {
		return resolvedApiCmds_;
	}

private:
	struct UnresolvedAPICmd {
		APICommand command;
		WGLSymbol *definingSymbol;
		int unresolvedDependencyCount;
	};

private:
	void markSymbolDefined(WGLSymbol *s);

private:
	std::vector<UnresolvedAPICmd> unresolvedApiCmds_;
	std::vector<APICommand> resolvedApiCmds_;
	std::unordered_set<WGLSymbol *> definedSymbols_;

	/// List of what api cmds depend on a given symbol
	std::unordered_multimap<WGLSymbol *, int> symbolApiCmdDependents_;

};

