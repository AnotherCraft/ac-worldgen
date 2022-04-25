#include "wga_symbol.h"

#include "main.h"

#include "util/assert.h"

WGA_Symbol::WGA_Symbol() {
	static size_t ixc = 0;
	ix = ixc++;

	{
		std::unique_lock _ml(dbgFileMutex);
		dbgFile << std::format("newSymbol {}\n", ix);
	}
}

WGA_Symbol::~WGA_Symbol() {
	{
		std::unique_lock _ml(dbgFileMutex);
		dbgFile << std::format("destroySymbol {}\n", ix);
	}
}

WGA_Symbol::SymbolType WGA_Symbol::symbolType() const {
	return SymbolType::Abstract;
}

bool WGA_Symbol::isContextual() const {
	return false;
}

WGA_Symbol::PragmaValue WGA_Symbol::pragma(const std::string &name) const {
	return pragmas_.at(name);
}

void WGA_Symbol::setPragma(const std::string &name, const PragmaValue &value) {
	// Only allow setting existing pargmas
	ASSERT(pragmas_.contains(name));
	pragmas_[name] = value;
}

void WGA_Symbol::setPragmas(const WGA_Symbol::PragmaList &pragmas) {
	for(auto it = pragmas.begin(), end = pragmas.end(); it != end; it++)
		setPragma(it->first, it->second);
}
