#include "wga_datarecord_cpu.h"

#include "worldgen/cpu/worldgenapi_cpu.h"
#include "wga_datacache_cpu.h"

WGA_DataRecord_CPU::Key::Key(WGA_Symbol *sym, const BlockWorldPos &origin, WGA_DataRecord_CPU::SubKey subKey)
	: symbol(sym), origin(origin), subKey(subKey) {

}

WGA_DataRecord_CPU::Key::Key(const WGA_DataRecord_CPU::Key &other)
	: symbol(other.symbol), origin(other.origin), subKey(other.subKey) {

}

std::strong_ordering WGA_DataRecord_CPU::Key::operator <=>(const WGA_DataRecord_CPU::Key &other) const {
	if(auto v = (symbol->ix <=> other.symbol->ix); v != 0)
		return v;

	if(auto v = (origin.x() <=> other.origin.x()); v != 0)
		return v;

	if(auto v = (origin.y() <=> other.origin.y()); v != 0)
		return v;

	if(auto v = (origin.z() <=> other.origin.z()); v != 0)
		return v;

	if(auto v = (subKey <=> other.subKey); v != 0)
		return v;

	return std::strong_ordering();
}
