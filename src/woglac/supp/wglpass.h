#pragma once

#include "wglinclude.h"

#include <QStack>

#include "wglcontext.h"
#include "wglsymbol.h"

class WGLPass : protected WoglacBaseListener {

public:
	WGLPass();

public:
	void setContext(WGLContext *ctx);

public:
	void execute(WoglacParser::ModuleContext *module);

protected:
	using ValueType = WGA_Value::ValueType;
	using SymbolType = WGLSymbol::Type;

protected:
	inline WGLSymbol *currentScope() {
		return currentScope_.top();
	}

	/// Looks for the extended identifier in the current symbol scope and parent scopes. Returns the current symbol if id is null.
	WGLSymbol *lookupIdentifier(WoglacParser::ExtendedIdentifierContext *eid, bool skipLast);

protected:
	void checkTargetTypeMatch(antlr4::Token *targetType, WGLSymbol *effectiveTarget, antlr4::ParserRuleContext *ctx);

	void popScope(antlr4::ParserRuleContext *ctx);

protected:
	WGLSymbol *
	componentNodeDeclaration(WoglacParser::ComponentNodeStatementCommonPartContext *ctx, WGLSymbol *directTarget,
	                         bool useDeclarationAST = true);

protected:
	WGLContext *ctx_;
	QStack<WGLSymbol *> currentScope_;

};

