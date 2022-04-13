#pragma once

// Must place before everything else because of antlr
#include "wglinclude.h"


#include "worldgen/base/worldgenapi.h"

#include "wglsymbol.h"

class WGLAPIContext {

public:
	WorldGenAPI *api;

public:
	void addSymbolMapping(WGLSymbol *wglSym, WGA_Symbol *wgaSym);

public:
	template<typename T>
	T *map(WGLSymbol *sym) const {
		ASSERT(!sym || symbolMapping_.contains(sym));
		return sym ? static_cast<T *>(symbolMapping_[sym]) : nullptr;
	};

private:
	QHash<WGLSymbol *, WGA_Symbol *> symbolMapping_;

};

