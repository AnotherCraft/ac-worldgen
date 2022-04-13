#include "wga_value_cpu.h"

#include "util/tracyutils.h"

WGA_Value_CPU::WGA_Value_CPU(WorldGenAPI_CPU &api, WGA_Value::ValueType valueType, bool isContextual, const DimensionalityFunc &dimFunc, const WGA_DataRecord_CPU::Ctor &ctor)
	: api_(api), valueType_(valueType), isContextual_(isContextual), dimFunc_(dimFunc), ctor_(ctor) {
	if(!isContextual_) {
		cachedDimensionality_ = dimFunc_();
		ASSERT(cachedDimensionality_ != Dimensionality::_count);
	}
}

WGA_Value_CPU::WGA_Value_CPU(WGA_Value_CPU *proxy)
	: WGA_Value_CPU(proxy->api_, proxy->valueType_, proxy->isContextual_, proxy->dimFunc_, nullptr) {
	proxy_ = proxy;
}

WGA_DataRecord_CPU::Ptr WGA_Value_CPU::getDataRecord(const BlockWorldPos &origin, WGA_DataRecord_CPU::SubKey subKey) {
	if(proxy_)
		return proxy_->getDataRecord(origin, subKey);

	WGA_DataRecord_CPU::Key key(this, origin, subKey);

	const Dimensionality dim = dimensionality();

	assert((origin & (chunkSize - 1)) == 0);

	if(dim == Dimensionality::DConst)
		key.origin = BlockWorldPos();

	else if(dim == Dimensionality::DPerChunk || dim == Dimensionality::D2D)
		key.origin.z() = 0;

	return api_.getDataRecord(key, ctor_);
}
