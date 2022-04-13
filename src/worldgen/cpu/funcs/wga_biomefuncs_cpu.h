#pragma once

#include "wga_funcs_cpu.h"
#include "../supp/wga_biomedata_cpu.h"

class WGA_BiomeFuncs_CPU : public WGA_Funcs_CPU {

public:
	template<VT t>
	static void biomeParam_nearest(Api api, Key key, DH <t> result, V <t> var);

	template<VT t>
	static void biomeParam_nearestSet(Api api, Key key, DH <t> result, V <t> var);

	template<VT t>
	static void biomeParam_weighted(Api api, Key key, DH <t> result, V <t> param, V <VT::Float> ipolParam);

};

template<WGA_Funcs_CPU::VT t>
void WGA_BiomeFuncs_CPU::biomeParam_nearest(Api api, Key key, DH <t> result, V <t> var) {
	const auto biomeDataPtr = api->getBiomeData(key.origin);
	const WGA_BiomeData_CPU &biomeData = biomeDataPtr->data;

	DH <t> dataHandles[WGA_BiomeData_CPU::maxCount];
	for(int i = 0; i < biomeData.count; i++)
		dataHandles[i] = V<t>(biomeData.biomes[i]->param(var.v)).dataHandle(key.origin);

	for(int i = 0; i < result.size; i++)
		result[i] = dataHandles[biomeData.nearestBiomes[i % chunkSurface]][i];
}

template<WGA_Funcs_CPU::VT t>
void WGA_BiomeFuncs_CPU::biomeParam_nearestSet(Api api, Key key, DH <t> result, V <t> var) {
	const auto biomeDataPtr = api->getBiomeData(key.origin);
	WGA_BiomeData_CPU &biomeData = biomeDataPtr->data;

	DH <t> dataHandles[WGA_BiomeData_CPU::maxCount];
	bool dataSet[WGA_BiomeData_CPU::maxCount];

	for(int i = 0; i < biomeData.count; i++) {
		dataHandles[i] = V<t>(biomeData.biomes[i]->param(var.v)).dataHandle(key.origin);
		dataSet[i] = biomeData.biomes[i]->param(var.v) != var.v;
	}

	for(int i = 0; i < result.size; i++) {
		const int nearestBiome = biomeData.nearestBiomes[i % chunkSurface];
		if(dataSet[nearestBiome]) {
			result[i] = dataHandles[nearestBiome][i];
		} else {
			float largestWeight = 0;
			int resultBiome = 0;

			for(int j = 0; j < biomeData.count; j++) {
				if(!dataSet[j])
					continue;

				const float weight = biomeData.weight[i % chunkSurface][j];
				if(weight > largestWeight) {
					largestWeight = weight;
					resultBiome = j;
				}
			}

			result[i] = dataHandles[resultBiome][i];
		}
	}
}

template<WGA_Funcs_CPU::VT t>
void WGA_BiomeFuncs_CPU::biomeParam_weighted(Api api, Key key, DH <t> result, V <t> param, V <VT::Float> ipolParam) {
	const auto biomeDataPtr = api->getBiomeData(key.origin);
	const WGA_BiomeData_CPU &biomeData = biomeDataPtr->data;

	DH <t> dataHandles[WGA_BiomeData_CPU::maxCount];
	for(int i = 0; i < biomeData.count; i++)
		dataHandles[i] = WGA_ValueWrapper_CPU<t>(biomeData.biomes[i]->param(param.v)).dataHandle(key.origin);

	const DH <VT::Float> paramHandle = ipolParam.dataHandle(key.origin);

	for(int i = 0; i < result.size; i++) {
		const float ipolParam = paramHandle[i];

		typename DH<t>::T sum = 0;
		float weightsSum = 0;

		for(int j = 0; j < biomeData.count; j++) {
			const float weightMetric = biomeData.weight[i % chunkSurface][j];
			const float weight = pow(weightMetric, ipolParam);
			weightsSum += weight;
			sum += dataHandles[j][i] * weight;
		}

		result[i] = sum / weightsSum;
	}
}
