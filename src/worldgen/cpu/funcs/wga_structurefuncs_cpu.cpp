#include "wga_structurefuncs_cpu.h"

#include <iostream>
#include <format>

#include "util/tracyutils.h"

#include "../supp/wga_structuregenerator_cpu.h"

void WGA_StructureFuncs_CPU::spawn2D(Api api, Key key, DH <VT::Block> result, V <VT::Rule> entryRule, V <VT::Float> maxRadius, V <VT::Float> seed, V <VT::Float> spawnZ, V <VT::Bool> spawnCondition) {
	const auto spawnFunc = [&spawnZ, &spawnCondition, &entryRule](Api api, Key key, SpawnList &spawnList) {
		ZoneScopedN("spawn2DSpawnFunc");

		WGA_DataHandle_CPU<VT::Float> spawnZHandle;
		{
			ZoneScopedN("spawnZHandle");
			spawnZHandle = spawnZ.dataHandle(key.origin);
		}

		WGA_DataHandle_CPU<VT::Bool> spawnConditionHandle;
		{
			ZoneScopedN("spawnConditionHandle");
			spawnConditionHandle = spawnCondition.dataHandle(key.origin);
		}

		WGA_DataHandle_CPU<VT::Rule> entryRuleHandle;
		{
			ZoneScopedN("entryRuleHandle");
			entryRuleHandle = entryRule.dataHandle(key.origin);
		}

		for(int i = 0; i < chunkSurface; i++) {
			const BlockWorldPos_T z = spawnZHandle[i];
			const int ix = i + z * chunkSurface;

			if(!(spawnConditionHandle[ix]))
				continue;

			spawnList.emplace_back(key.origin + BlockWorldPos(i % chunkSize, i / chunkSize, z), api->mapToSymbol<WGA_Rule>(entryRuleHandle[ix]));
		}
	};

	_spawn(api, key, result, maxRadius, seed, spawnFunc);
}

void WGA_StructureFuncs_CPU::worldPos(Api api, Key key, DH <VT::Float3> result, V <VT::ComponentNode> node) {
	WGA_SF_NODE_POS_SHENANIGANS(nodeWorldPos.to<float>())
}

void WGA_StructureFuncs_CPU::localPos(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float3> result) {
	ASSERT(api->structureGen);

	const BlockTransformMatrix m = api->structureGen->currentDataContext()->localToWorldMatrix().nonScalingInverted();
	const BlockWorldPos base = m * result.worldPos(key.origin, 0);
	const BlockWorldPos vx = (m * result.worldPos(key.origin, 1)) - base;
	const BlockWorldPos vy = (m * result.worldPos(key.origin, chunkSize)) - base;
	const BlockWorldPos vz = (m * result.worldPos(key.origin, chunkSurface)) - base;

	{
		int i = 0;
		for(int z = 0; z < chunkSize; z++) {
			for(int y = 0; y < chunkSize; y++) {
				for(int x = 0; x < chunkSize; x++) {
					result[i++] = (base + vx * x + vy * y + vz * z).to<float>();
				}
			}
		}
	}
}

void WGA_StructureFuncs_CPU::localSeed(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float> result) {
	if(!api->structureGen)
		throw std::exception("localSeed() called outside structure generation");

	// Mod by 65535 so the float does not lose precision, should be okay for most shenanigans
	result[0] = Vector<float, 1>(api->structureGen->currentDataContext()->seed() % 65535);
}

void WGA_StructureFuncs_CPU::distanceTo(Api api, Key key, DH <VT::Float> result, V <VT::ComponentNode> node) {
	WGA_SF_NODE_POS_SHENANIGANS((nodeWorldPos.to<float>() - worldPos.to<float>()).length());
}

void WGA_StructureFuncs_CPU::randL(WGA_Funcs_CPU::Api api, const WGA_DataRecord_CPU::Key &key, WGA_Funcs_CPU::DH<VT::Float> result, WGA_Funcs_CPU::V<VT::Float> seed) {
	if(!api->structureGen)
		throw std::exception("localSeed() called outside structure generation");

	const Seed seedv = WorldGen_CPU_Utils::hash(api->structureGen->currentDataContext()->seed(), static_cast<Seed>(seed.constValue()));
	result[0] = static_cast<float>(seedv & 65535) / 65535.0f;
}

void WGA_StructureFuncs_CPU::_spawn(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <VT::Block> result, V <VT::Float> maxRadius, V <VT::Float> seed, const WGA_StructureFuncs_CPU::SpawnFunc &spawnFunc) {
	ZoneScoped;

	ASSERT(result.size == chunkVolume);

	for(int i = 0; i < result.size; i++)
		result[i] = blockID_undefined;

	/**
	 *  This implementation uses subkeys:
	 *  0 for actual block output
	 *  1 for structure records (those are marked as cross sampled)
	 */

	static_cast<WGA_Value_CPU *>(key.symbol)->markAsCrossSampled(1);

	const auto ctor = [&api, &seed, &spawnFunc](const WGA_DataRecord_CPU::Key &key) {
		ZoneScopedN("genStructure");

		auto rec = std::make_shared<StructureRec>();

		SpawnList spawnList;
		spawnFunc(api, key, spawnList);

		const WorldGenSeed seedV = static_cast<WorldGenSeed>(WGA_ValueWrapper_CPU<VT::Float>(seed).constValue());

		WGA_StructureGenerator_CPU structGen(*api);

		for(const SpawnRec &spawnRec: spawnList) {
			ZoneScopedN("processSpawnRec");

			structGen.setup(spawnRec.entryRule, spawnRec.origin, seedV);

			if(!structGen.process())
				continue;

			WGA_StructureOutputData_CPUPtr output = structGen.generateOutput();
			rec->data.push_back(output);
			rec->dataSizeV += output->dataSize;
		}

		return std::static_pointer_cast<WGA_DataRecord_CPU>(rec);
	};


	const ChunkWorldPos originChunk = key.origin.chunkPosition();
	const ChunkWorldPos_T maxRadiusV = static_cast<ChunkWorldPos_T>(maxRadius.constValue());
	for(const ChunkWorldPos &pos: vectorIterator(originChunk - maxRadiusV, originChunk + maxRadiusV)) {
		const WGA_DataRecord_CPU::Key recKey(key.symbol, BlockWorldPos::fromChunkBlockIndex(pos, 0, 0), 1);
		const StructureRecPtr rec = std::static_pointer_cast<StructureRec>(api->getDataRecord(recKey, ctor));

		for(const WGA_StructureOutputData_CPUPtr &struc: rec->data) {
			ZoneScopedN("procStructureData");

			if(!struc->subChunkRecords.contains(key.origin))
				continue;

			const auto schr = struc->subChunkRecords.at(key.origin);

			if(!schr.flatData.empty()) {
				ASSERT(schr.associativeData.empty());

				const auto dt = schr.flatData.data();
				for(int i = 0; i < chunkVolume; i++) {
					if(auto v = dt[i]; v != blockID_undefined)
						result[i] = v;
				}
			}
			else
				for(const auto &v: schr.associativeData) {
					ASSERT(v.second != blockID_undefined);
					result[v.first] = v.second;
				}
		}
	}
}
