#include "wga_utilityfuncs_cpu.h"

#include "util/tracyutils.h"

void WGA_UtilityFuncs_CPU::smoothMin(Api api, Key key, DH <VT::Float> result, V <VT::Float> a, V <VT::Float> b, V <VT::Float> k) {
	Q_UNUSED(api)

	const auto ah = a.dataHandle(key.origin), bh = b.dataHandle(key.origin), kh = k.dataHandle(key.origin);

	for(int i = 0; i < result.size; i++) {
		const auto a = ah[i], b = bh[i], k = kh[i];
		const float h = qBound<float>(0, 0.5f + 0.5f * (a - b) / k, 1);
		const float hInv = 1.0f - h;
		result[i] = (a - k * h) * hInv + b * h;
	}
}

void WGA_UtilityFuncs_CPU::smoothMax(Api api, Key key, DH <VT::Float> result, V <VT::Float> a, V <VT::Float> b, V <VT::Float> k) {
	Q_UNUSED(api)

	const auto ah = a.dataHandle(key.origin), bh = b.dataHandle(key.origin), kh = k.dataHandle(key.origin);

	for(int i = 0; i < result.size; i++) {
		const auto a = ah[i], b = bh[i], k = kh[i];
		const float h = qBound<float>(0, 0.5f + 0.5f * (b - a) / k, 1);
		const float hInv = 1.0f - h;
		result[i] = (a + k * h) * hInv + b * h;
	}
}

void WGA_UtilityFuncs_CPU::minPC(Api api, Key key, DH <VT::Float> result, V <VT::Float> valv) {
	Q_UNUSED(api)
	ASSERT(valv.dimensionality() <= Dimensionality::D2D);

	const auto ah = valv.dataHandle(key.origin);

	float min = ah[0];
	for(int i = 1; i < ah.size; i++)
		min = qMin<float>(min, ah[i]);

	result[0] = min;
}

void WGA_UtilityFuncs_CPU::maxPC(Api api, Key key, DH <VT::Float> result, V <VT::Float> valv) {
	Q_UNUSED(api)
	ASSERT(valv.dimensionality() <= Dimensionality::D2D);

	const auto ah = valv.dataHandle(key.origin);

	float min = ah[0];
	for(int i = 1; i < ah.size; i++)
		min = qMax<float>(min, ah[i]);

	result[0] = min;
}

void WGA_UtilityFuncs_CPU::distanceToLine(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float> result, V <WGA_Value::ValueType::Float3> p, V <WGA_Value::ValueType::Float3> a, V <WGA_Value::ValueType::Float3> b) {
	Q_UNUSED(api)

	const auto ah = a.dataHandle(key.origin), bh = b.dataHandle(key.origin), ph = p.dataHandle(key.origin);

	for(int i = 0; i < result.size; i++) {
		const V3F a = ah[i], b = bh[i], p = ph[i];
		const V3F abDiff = b - a;
		result[i] = abDiff.crossProduct(a - p).length() / abDiff.length();
	}
}
