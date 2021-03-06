#pragma once

// Must place before everything else because of antlr
#include "wglinclude.h"

#include "worldgen/base/worldgenapi.h"

#include "wglsymbol.h"
#include "wgldefines.h"

class WGLAPIContext {

public:
	WorldGenAPI *api;

public:
	void addSymbolMapping(WGLSymbol *wglSym, WGA_Symbol *wgaSym);

public:
	template<typename T>
	T *map(const WGLSymbol *sym) const {
		ASSERT(!sym || symbolMapping_.contains(sym));
		return sym ? static_cast<T *>(symbolMapping_.at(sym)) : nullptr;
	};

	WGA_Value *expr(const WGLExpressionResult &expr);

private:
	std::unordered_map<const WGLSymbol *, WGA_Symbol *> symbolMapping_;
	std::unordered_map<std::string, WGA_Value*> exprCache_;

};

