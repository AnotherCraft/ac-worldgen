#pragma once

#include "wga_funcs_cpu.h"

class WGA_UtilityFuncs_CPU : public WGA_Funcs_CPU {

public:
	template<VT t>
	static void select(Api api, Key key, DH <t> result, V <VT::Bool> cond, V <t> thn, V <t> els);

public:
	static void smoothMin(Api api, Key key, DH <VT::Float> result, V <VT::Float> a, V <VT::Float> b, V <VT::Float> k);
	static void smoothMax(Api api, Key key, DH <VT::Float> result, V <VT::Float> a, V <VT::Float> b, V <VT::Float> k);

	static void minPC(Api api, Key key, DH <VT::Float> result, V <VT::Float> val);
	static void maxPC(Api api, Key key, DH <VT::Float> result, V <VT::Float> val);

public:
	static void
	distanceToLine(Api api, Key key, DH <VT::Float> result, V <VT::Float3> p, V <VT::Float3> a, V <VT::Float3> b);

public:
	template<VT t>
	static void lengthExp(Api api, Key key, DH <VT::Float> result, V <t> v, V <VT::Float> exp) {
		const auto vh = v.dataHandle(key.origin);
		const auto exph = exp.dataHandle(key.origin);

		for(int i = 0; i < result.size; i++) {
			const auto vec = vh[i].abs();
			const auto expv = exph[i];

			float r = 0;
			for(int j = 0; j < V<t>::T::D; j++)
				r += pow(vec[j], expv);

			result[i] = pow(r, 1.0f / expv);
		}
	}

};

template<WGA_Funcs_CPU::VT t>
void WGA_UtilityFuncs_CPU::select(Api api, Key key, DH <t> result, V <VT::Bool> condv, V <t> thnv, V <t> elsv) {
	auto cond = condv.dataHandle(key.origin);

	int ac = 0;
	for(int i = 0; i < cond.size; i++)
		ac += cond[i];

	// Everything false -> just b
	if(ac == 0) {
		auto vh = elsv.dataHandle(key.origin);
		for(int i = 0; i < result.size; i++)
			result[i] = vh[i];
	}
		// Everything true -> just a
	else if(ac == cond.size) {
		auto vh = thnv.dataHandle(key.origin);
		for(int i = 0; i < result.size; i++)
			result[i] = vh[i];
	}

	else {
		auto thnh = thnv.dataHandle(key.origin);
		auto elsh = elsv.dataHandle(key.origin);
		for(int i = 0; i < result.size; i++)
			result[i] = cond[i] ? thnh[i] : elsh[i];
	}
}
