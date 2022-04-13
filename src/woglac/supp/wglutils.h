#pragma once

#include "wglinclude.h"

#include <QString>

class WGLSymbol;

class WGLUtils {

public:
	enum class SymbolType {
		Unknown,
		Namespace,
		Scope,
		Biome,
		Component,
		Rule,
		RuleExpansion,
		BiomeParam,
		StructureParam,
		FieldVariable,
		StructureVariable,
		ComponentNode,
	};

public:
	static SymbolType getSymbolType(const antlr4::Token *val);
	static const QString &getSymbolTypeName(SymbolType t);

public:
	static QString identifier(const antlr4::Token *id);
	static float numericLiteral(const antlr4::Token *val);
	static QString stringLiteral(const antlr4::Token *val);

};

