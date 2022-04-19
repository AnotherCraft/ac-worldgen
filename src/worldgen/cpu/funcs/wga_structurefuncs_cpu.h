#pragma once

#include "wga_funcs_cpu.h"

#include "util/quickcache.h"

#include "worldgen/base/supp/wga_componentnode.h"

#define WGA_SF_NODE_POS_SHENANIGANS(expr) \
  ASSERT(WorldGenAPI_CPU::structureGen); \
  WGA_StructureGenerator_CPU::DataContext *ctx = WorldGenAPI_CPU::structureGen->currentDataContext(); \
  const BlockWorldPos constSamplePos = ctx->constSamplePos(); \
  auto nodeh = node.dataHandle(key.origin); \
  QuickCache<WGA_SymbolID_CPU> nodePosCache; \
  BlockWorldPos nodeLocalPos, nodeWorldPos;\
  \
  for(int i = 0; i < result.size; i++) { \
  const WGA_SymbolID_CPU nodeID = nodeh[i];\
  if(!nodePosCache.isAndSet(nodeID)) {\
  WGA_ComponentNode *nodev = api->mapToSymbol<WGA_ComponentNode>(nodeh[i]); \
  ASSERT(nodev->parentComponent() == ctx->associatedSymbol()); \
  nodeLocalPos = WGA_ValueWrapper_CPU<VT::Float3>(nodev->config().position).sampleAt(constSamplePos).to<BlockWorldPos_T>(); \
  nodeWorldPos = ctx->mapToWorld(nodeLocalPos); \
  } \
  const BlockWorldPos worldPos = result.worldPos(key.origin, i); \
  result[i] = expr; \
  }

class WGA_StructureFuncs_CPU : public WGA_Funcs_CPU {

public:
	static void
	spawn2D(Api api, Key key, DH <VT::Block> result, V <VT::Rule> rule, V <VT::Float> maxRadius, V <VT::Float> seed, V <VT::Float> spawnZ, V <VT::Bool> spawnCondition);

public:
	static void worldPos(Api api, Key key, DH <VT::Float3> result, V <VT::ComponentNode> node);
	static void localPos(Api api, Key key, DH <VT::Float3> result);
	static void localSeed(Api api, Key key, DH <VT::Float> result);

	static void distanceTo(Api api, Key key, DH <VT::Float> result, V <VT::ComponentNode> node);

	template<VT t>
	static void sampleAt(Api api, Key key, DH <t> result, V <t> value, V <VT::ComponentNode> node);

private:
	using StructureRec = WGA_StructureOutputDataRecord_CPU;
	using StructureRecPtr = std::shared_ptr<StructureRec>;

private:
	struct SpawnRec {
		BlockWorldPos origin;
		WGA_Rule *entryRule;
	};
	using SpawnList = std::vector<SpawnRec>;
	using SpawnFunc =
	std::function< void(Api
	api,
	Key key, SpawnList
	&spawnList)>;

private:
	static void _spawn(Api api, Key key, DH <VT::Block> result, V <VT::Float> maxRadius, V <VT::Float> seed, const SpawnFunc &spawnFunc);

};

template<WGA_StructureFuncs_CPU::VT t>
void WGA_StructureFuncs_CPU::sampleAt(Api api, Key key, DH <t> result, V <t> value, V <VT::ComponentNode> node) {
	WGA_SF_NODE_POS_SHENANIGANS(value.sampleAt(nodeWorldPos))
}
