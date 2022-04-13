#pragma once

#include <QVector>

#include "worldgen/base/worldgenapi.h"

#include "supp/wga_datacache_cpu.h"
#include "supp/wga_valuerecs_cpu.h"
#include "supp/wga_datarecord_cpu.h"

class WorldGenAPI_CPU : public WorldGenAPI {

public:
	using Dimensionality = WGA_Value::Dimensionality;
	using ValueType = WGA_Value::ValueType;

public:
	WorldGenAPI_CPU();
	virtual ~WorldGenAPI_CPU();

public:
	/// Used for resolving local variables
	static thread_local WGA_StructureGenerator_CPU *structureGen;

public:
	virtual WGA_Value *constFloat(float val) override;
	virtual WGA_Value *constFloat3(const V3F val) override;
	virtual WGA_Value *constBlock(BlockID val) override;
	virtual WGA_Value *constBool(bool val) override;
	virtual WGA_Value *constRule(WGA_Rule *val) override;
	virtual WGA_Value *constComponentNode(WGA_ComponentNode *val) override;

public:
	virtual WGA_Biome *newBiome() override;
	virtual WGA_Rule *newRule() override;
	virtual WGA_RuleExpansion *newRuleExpansion(WGA_Rule *rule, WGA_Component *component, const QString &node) override;
	virtual WGA_Component *newComponent() override;
	virtual WGA_ComponentNode *newComponentNode() override;

public:
	virtual WGA_Value *function(FunctionID function, const FunctionArgs &args) override;
	virtual WGA_Value *proxy(WGA_Value *v) override;
	virtual WGA_Value *grammarSymbolParam(WGA_GrammarSymbol *sym, const QString &name, WGA_Value::ValueType type, WGA_Value *defaultValue) override;

public:
	WGA_DataRecord_CPU::Ptr getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor);
	WGA_Biome &getChunkBiome(const BlockWorldPos &origin);
	QSharedPointer<WGA_DataRecordT_CPU<WGA_BiomeData_CPU> > getBiomeData(const BlockWorldPos &origin);

	/// Creates thread local cache for data (saves some mutex collisions)
	void createLocalCache();
	void destroyLocalCache();

	void reportCacheHitRate();

	template<typename T>
	inline T *mapToSymbol(WGA_SymbolID_CPU id) {
		ASSERT(idSymbolMapping_.contains(id));
		return static_cast<T *>(idSymbolMapping_[id]);
	}

public:
	template<typename T>
	inline T *registerSymbol(T *sym) {
		symbols_ += sym;
		return sym;
	}

private:
	inline auto &api() {
		return *this;
	}

private:
	WGA_SymbolID_CPU mapSymbol(WGA_Symbol *sym);

private:
	WGA_Symbol chunkBiomeSymbol_, biomeDataSymbol_;

private:
	QHash<WGA_Symbol *, WGA_SymbolID_CPU> symbolIDMapping_;
	QHash<WGA_SymbolID_CPU, WGA_Symbol *> idSymbolMapping_;
	QVector<WGA_Symbol *> symbols_;
	QVector<WGA_Biome *> biomes_;

private:
	WGA_DataCache_CPU dataCache_;

};
