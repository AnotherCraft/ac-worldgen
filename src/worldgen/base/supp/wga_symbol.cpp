#include "wga_symbol.h"

#include "util/assert.h"

WGA_Symbol::WGA_Symbol() {

}

WGA_Symbol::~WGA_Symbol() {

}

WGA_Symbol::SymbolType WGA_Symbol::symbolType() const {
	return SymbolType::Abstract;
}

bool WGA_Symbol::isContextual() const {
	return false;
}

QVariant WGA_Symbol::pragma(const QString &name) const {
	ASSERT(pragmas_.contains(name));
	return pragmas_[name];
}

void WGA_Symbol::setPragma(const QString &name, const QVariant &value) {
	// Only allow setting existing pargmas
	ASSERT(pragmas_.contains(name));
	pragmas_[name] = value;
}

void WGA_Symbol::setPragmas(const WGA_Symbol::PragmaList &pragmas) {
	for(auto it = pragmas.begin(), end = pragmas.end(); it != end; it++)
		setPragma(it.key(), it.value());
}
