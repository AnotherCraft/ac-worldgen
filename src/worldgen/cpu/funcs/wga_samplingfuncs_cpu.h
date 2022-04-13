#pragma once

#include "wga_funcs_cpu.h"

class WGA_SamplingFuncs_CPU : public WGA_Funcs_CPU {

public:
	template<VT t>
	static void sampleOffset(Api api, Key key, DH <t> result, V <t> value, V <VT::Float3> offsetv);

	template<VT t>
	static void sampleAt(Api api, Key key, DH <t> result, V <t> value, V <VT::Float3> pos);

	template<VT t>
	static void sampleAt(Api api, Key key, DH <t> result, V <t> value, V <VT::Float2> pos);

	static void sampleGradient2D(Api api, Key key, DH <VT::Float2> result, V <VT::Float> value, V <VT::Float> dist);

	template<VT t>
	static void sampleAvg2D(Api api, Key key, DH <t> result, V <t> value, V <VT::Float> dist);

};

template<WGA_Funcs_CPU::VT t>
void WGA_SamplingFuncs_CPU::sampleOffset(Api api, Key key, DH <t> result, V <t> value, V <VT::Float3> offsetv) {
	Q_UNUSED(api)

	value.v->markAsCrossSampled(0);

	auto offseth = offsetv.dataHandle(key.origin);

	for(int i = 0; i < result.size; i++)
		result[i] = value.sampleAt(result.worldPos(key.origin, i) + offseth[i].to<BlockWorldPos_T>());
}

template<WGA_Funcs_CPU::VT t>
void WGA_SamplingFuncs_CPU::sampleAt(Api api, Key key, DH <t> result, V <t> value, V <VT::Float3> posv) {
	Q_UNUSED(api)

	value.v->markAsCrossSampled(0);

	DH <VT::Float3> posh = posv.dataHandle(key.origin);
	for(int i = 0; i < result.size; i++)
		result[i] = value.sampleAt(posh[i].to<BlockWorldPos_T>());
}

template<WGA_Funcs_CPU::VT t>
void WGA_SamplingFuncs_CPU::sampleAt(Api api, Key key, DH <t> result, V <t> value, V <VT::Float2> posv) {
	Q_UNUSED(api)

	value.v->markAsCrossSampled(0);

	DH <VT::Float2> posh = posv.dataHandle(key.origin);
	for(int i = 0; i < result.size; i++)
		result[i] = value.sampleAt(V3F(posh[i], 0).to<BlockWorldPos_T>());
}

template<WGA_Funcs_CPU::VT t>
void WGA_SamplingFuncs_CPU::sampleAvg2D(Api api, Key key, DH <t> result, V <t> value, V <VT::Float> dist) {
	Q_UNUSED(api)

	value.v->markAsCrossSampled(0);

	// Each sampling point will have its own separate cache
	auto valXp = value, valXm = value, valYp = value, valYm = value;

	const float coef = 1.0f / 5.0f;

	const auto disth = dist.dataHandle(key.origin);
	const auto valh = value.dataHandle(key.origin);

	for(int i = 0; i < result.size; i++) {
		const BlockWorldPos worldPos = result.worldPos(key.origin, i);
		const BlockWorldPos_T distv = static_cast<BlockWorldPos_T>(disth[i]);

		result[i] =
			(
				valh[i]
				+ valXp.sampleAt(worldPos + BlockWorldPos(distv, 0, 0)) + valXm.sampleAt(worldPos - BlockWorldPos(distv, 0, 0))
				+ valYp.sampleAt(worldPos + BlockWorldPos(0, distv, 0)) + valYm.sampleAt(worldPos - BlockWorldPos(0, distv, 0))
			) * coef;
	}
}
