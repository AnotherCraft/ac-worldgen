#include "wglapicontext.h"

void WGLAPIContext::addSymbolMapping(WGLSymbol *wglSym, WGA_Symbol *wgaSym) {
	ASSERT(!symbolMapping_.contains(wglSym));
	wgaSym->setDescription(wglSym->name().empty() ? wglSym->desc() : wglSym->fullName());
	symbolMapping_[wglSym] = wgaSym;
}

WGA_Value *WGLAPIContext::expr(const WGLExpressionResult &expr) {
	WGA_Value *&r = exprCache_[*expr.signature];
	if(!r)
		r = expr.func(*this);

	ASSERT(r->valueType() == expr.type);
	return r;
}
