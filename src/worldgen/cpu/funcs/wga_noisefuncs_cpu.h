#pragma once

#include "wga_funcs_cpu.h"

class WGA_NoiseFuncs_CPU : public WGA_Funcs_CPU {

public:
	static inline void randC(Api api, Key key, DH <VT::Float> result, V <VT::Float> seed) {
		rand(api, key, result, seed);
	}

	static inline void randPC(Api api, Key key, DH <VT::Float> result, V <VT::Float> seed) {
		rand(api, key, result, seed);
	}

	static inline void rand2D(Api api, Key key, DH <VT::Float> result, V <VT::Float> seed) {
		rand(api, key, result, seed);
	}

	static inline void rand3D(Api api, Key key, DH <VT::Float> result, V <VT::Float> seed) {
		rand(api, key, result, seed);
	}

	static void valueNoisePC(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed, V <VT::Float> value);
	static void valueNoise2D(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed, V <VT::Float> value);

	static void perlin2D(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed);
	static void perlin3D(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed);

	static void voronoi2D(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed, V <VT::Float> resultType, V <VT::Float> metricExponent);
	static void voronoi2DColored(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed, V <VT::Float> resultType, V <VT::Float> metricExponent, V <VT::Float> coloring);

	static void voronoi3D(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed, V <VT::Float> resultType, V <VT::Float> metricExponent);
	static void voronoi3DParam(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed, V <VT::Float> resultType, V <VT::Float> metricExponent, V <VT::Float> param);

	static void poissonDisc2DBool(Api api, Key key, DH <VT::Bool> result, V <VT::Float> seed, V <VT::Float> radius);

	static void osimplex2D(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed);
	static void osimplex3D(Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSize, V <VT::Float> seed);

private:
	static void rand(Api api, Key key, DH <VT::Float> result, V <VT::Float> seed);

	static BlockWorldPos adjustOrigin(const BlockWorldPos &o, Seed seed);

};

