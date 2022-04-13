#include "wga_structurefuncs_cpu.h"

#include "util/tracyutils.h"

#include "../supp/wga_structuregenerator_cpu.h"

void WGA_StructureFuncs_CPU::spawn2D(Api api, Key key, DH <VT::Block> result, V <VT::Rule> entryRule, V <VT::Float> maxRadius, V <VT::Float> seed, V <VT::Float> spawnZ, V <VT::Bool> spawnCondition) {
	const auto spawnFunc = [&spawnZ, &spawnCondition, &entryRule](Api api, Key key, SpawnList &spawnList) {
		const auto spawnZHandle = spawnZ.dataHandle(key.origin);
		const auto spawnConditionHandle = spawnCondition.dataHandle(key.origin);
		const auto entryRuleHandle = entryRule.dataHandle(key.origin);

		for(int i = 0; i < chunkSurface; i++) {
			const BlockWorldPos_T z = spawnZHandle[i];
			const int ix = i + z * chunkSurface;

			if(!(spawnConditionHandle[ix]))
				continue;

			spawnList += SpawnRec{
				key.origin + BlockWorldPos(i % chunkSize.x(), i / chunkSize.x(), z),
				api->mapToSymbol<WGA_Rule>(entryRuleHandle[ix])
			};
		}
	};

	_spawn(api, key, result, maxRadius, seed, spawnFunc);
}

void WGA_StructureFuncs_CPU::worldPos(Api api, Key key, DH <VT::Float3> result, V <VT::ComponentNode> node) {
	WGA_SF_NODE_POS_SHENANIGANS(nodeWorldPos.to<float>())
}

#pragma optimize("gt", on)

void WGA_StructureFuncs_CPU::localPos(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float3> result) {
	Q_UNUSED(api);
	ASSERT(api->structureGen);

	const BlockTransformMatrix m = api->structureGen->currentDataContext()->localToWorldMatrix().nonScalingInverted();
	const BlockWorldPos base = m * result.worldPos(key.origin, 0);
	const BlockWorldPos vx = (m * result.worldPos(key.origin, 1)) - base;
	const BlockWorldPos vy = (m * result.worldPos(key.origin, chunkSize.x())) - base;
	const BlockWorldPos vz = (m * result.worldPos(key.origin, chunkSurface)) - base;

	{
		int i = 0;
		for(int z = 0; z < chunkSize.z(); z++) {
			for(int y = 0; y < chunkSize.y(); y++) {
				for(int x = 0; x < chunkSize.x(); x++) {
					result[i++] = (base + vx * x + vy * y + vz * z).to<float>();
				}
			}
		}
	}
}

void WGA_StructureFuncs_CPU::localSeed(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float> result) {
	Q_UNUSED(api);
	Q_UNUSED(key);

	ASSERT(api->structureGen);

	result[0] = Vector<float, 1>(api->structureGen->currentDataContext()->seed());
}

void WGA_StructureFuncs_CPU::distanceTo(Api api, Key key, DH <VT::Float> result, V <VT::ComponentNode> node) {
	WGA_SF_NODE_POS_SHENANIGANS((nodeWorldPos.to<float>() - worldPos.to<float>()).length());
}

void WGA_StructureFuncs_CPU::_spawn(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <VT::Block> result, V <VT::Float> maxRadius, V <VT::Float> seed, const WGA_StructureFuncs_CPU::SpawnFunc &spawnFunc) {
	ZoneScoped;

	ASSERT(result.size == subChunkVolume);

	for(int i = 0; i < result.size; i++)
		result[i] = blockID_undefined;

	/**
	 *  This implementation uses subkeys:
	 *  0 for actual block output
	 *  1 for structure records (those are marked as cross sampled)
	 */

	static_cast<WGA_Value_CPU *>(key.symbol)->markAsCrossSampled(1);

	const auto ctor = [&api, &seed, &spawnFunc](const WGA_DataRecord_CPU::Key &key) {
		StructureRecPtr rec(new StructureRec());

		SpawnList spawnList;
		spawnFunc(api, key, spawnList);

		const WorldGen::Seed seedV = static_cast<WorldGen::Seed>(WGA_ValueWrapper_CPU<VT::Float>(seed).constValue());

		WGA_StructureGenerator_CPU structGen(*api);

		for(const SpawnRec &spawnRec: qAsConst(spawnList)) {
			structGen.setup(spawnRec.entryRule, spawnRec.origin, seedV);

			if(!structGen.process())
				continue;

			WGA_StructureOutputData_CPUPtr output = structGen.generateOutput();
			rec->data += output;
			rec->dataSizeV += output->dataSize;
		}

		return rec.staticCast<WGA_DataRecord_CPU>();
	};


	const ChunkWorldPos originChunk = key.origin.chunkPosition();
	const ChunkWorldPos_T maxRadiusV = static_cast<ChunkWorldPos_T>(maxRadius.constValue());
	for(const ChunkWorldPos &pos: vectorIterator(originChunk - maxRadiusV, originChunk + maxRadiusV)) {
		const WGA_DataRecord_CPU::Key recKey(key.symbol, BlockWorldPos::fromChunkBlockIndex(pos, 0, 0), 1);
		const StructureRecPtr rec = api->getDataRecord(recKey, ctor).staticCast<StructureRec>();

		for(const WGA_StructureOutputData_CPUPtr &struc: qAsConst(rec->data)) {
			if(!struc->subChunkRecords.contains(key.origin))
				continue;

			const auto schr = struc->subChunkRecords.value(key.origin);

			if(!schr.flatData.isEmpty()) {
				ASSERT(schr.associativeData.isEmpty());

				const auto dt = schr.flatData.constData();
				for(int i = 0; i < subChunkVolume; i++) {
					if(dt[i] != blockID_undefined)
						result[i] = dt[i];
				}
			}
			else
				for(const auto &v: schr.associativeData)
					result[v.first] = v.second;
		}
	}
}
