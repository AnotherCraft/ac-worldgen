#include "wglapicontext.h"

void WGLAPIContext::addSymbolMapping(WGLSymbol *wglSym, WGA_Symbol *wgaSym) {
	ASSERT(!symbolMapping_.contains(wglSym));
	wgaSym->setDestription(wglSym->desc());
	symbolMapping_[wglSym] = wgaSym;
}
