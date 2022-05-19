#include "wga_samplingfuncs_cpu.h"


void WGA_SamplingFuncs_CPU::sampleGradient2D(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <VT::Float2> result, V <VT::Float> value, V <VT::Float> dist) {
	value.v->markAsCrossSampled(0);

	// Each sampling point will have its own separate cache
	auto valXp = value, valXm = value, valYp = value, valYm = value;

	const auto disth = dist.dataHandle(key.origin);
	for(int i = 0; i < result.size; i++) {
		const BlockWorldPos worldPos = result.worldPos(key.origin, i);

		const float distf = disth[i];
		const BlockWorldPos_T dist = static_cast<BlockWorldPos_T>(distf);
		const float coef = 1 / (1 + 2 * distf);

		result[i] = Vector2F(
			valXp.sampleAt(worldPos + BlockWorldPos(dist, 0, 0)) - valXm.sampleAt(worldPos - BlockWorldPos(dist, 0, 0)),
			valYp.sampleAt(worldPos + BlockWorldPos(0, dist, 0)) - valYm.sampleAt(worldPos - BlockWorldPos(0, dist, 0))
		) * coef;
	}
}
