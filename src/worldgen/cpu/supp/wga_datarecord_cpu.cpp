#include "wga_datarecord_cpu.h"

#include "worldgen/cpu/worldgenapi_cpu.h"
#include "wga_datacache_cpu.h"

WGA_DataRecord_CPU::Key::Key(WGA_Symbol *sym, const BlockWorldPos &origin, WGA_DataRecord_CPU::SubKey subKey)
	: symbol(sym), origin(origin), subKey(subKey) {

}

WGA_DataRecord_CPU::Key::Key(const WGA_DataRecord_CPU::Key &other)
	: symbol(other.symbol), origin(other.origin), subKey(other.subKey) {

}
