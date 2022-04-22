#include "wglapicontext.h"

void WGLAPIContext::addSymbolMapping(WGLSymbol *wglSym, WGA_Symbol *wgaSym) {
	ASSERT(!symbolMapping_.contains(wglSym));
	wgaSym->setDescription(wglSym->name().empty() ? wglSym->desc() : wglSym->fullName());
	symbolMapping_[wglSym] = wgaSym;
}
