#pragma once

// Must place before everything else because of antlr
#include "wglinclude.h"

#include "wglsymbol.h"
#include "wglapicontext.h"

class WGLContext {

public:
	using APICommand = std::function<void(WGLAPIContext &)>;
	using DependencyList = QSet<WGLSymbol *>;

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

	inline const QVector<APICommand> &apiCommands() {
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
	QList<UnresolvedAPICmd> unresolvedApiCmds_;
	QVector<APICommand> resolvedApiCmds_;
	QSet<WGLSymbol *> definedSymbols_;

	/// List of what api cmds depend on a given symbol
	QMultiHash<WGLSymbol *, int> symbolApiCmdDependents_;

};

