#include "worldgenapi_cpu.h"

#include <cmath>

#include "util/iterators.h"

#include "worldgen/base/supp/wga_componentnode.h"

#include "supp/wga_biomedata_cpu.h"
#include "supp/wga_value_cpu.h"
#include "supp/wga_fillfunc_cpu.h"
#include "supp/wga_valuewrapper_cpu.h"
#include "funcs/wga_funcs_cpu.h"

#define WGCPUF_ARGS(T) const WGA_DataRecord_CPU::Key &key, WGA_DataHandle_CPU<WGA_Value::ValueType::T> data
#define DIM_FUNC(D) [] { return WGA_Value::Dimensionality::D; }
#define WGCPUF_CONST(T, expr) api->registerSymbol(new WGA_Value_CPU(*api, WGA_Value::ValueType::T, false, DIM_FUNC(DConst), wga_fillCtor<WGA_Value::ValueType::T>(DIM_FUNC(DConst), [val = (expr)] (WGCPUF_ARGS(T)) { Q_UNUSED(key) data[0] = val; }, __FUNCTION__)))

using LocalCache = QHash<WGA_DataRecord_CPU::Key, WGA_DataRecord_CPU::Ptr>;

thread_local WGA_StructureGenerator_CPU *WorldGenAPI_CPU::structureGen = nullptr;
thread_local LocalCache *localCache = nullptr;

WorldGenAPI_CPU::~WorldGenAPI_CPU() {
	qDeleteAll(symbols_);
	symbols_.clear();
}

WGA_Value *WorldGenAPI_CPU::constFloat(float val) {
	auto api = this;
	return WGCPUF_CONST(Float, val);
}

WGA_Value *WorldGenAPI_CPU::constFloat3(const V3F val) {
	auto api = this;
	return WGCPUF_CONST(Float3, val);
}

WGA_Value *WorldGenAPI_CPU::constBlock(BlockID val) {
	auto api = this;
	return WGCPUF_CONST(Block, val);
}

WGA_Value *WorldGenAPI_CPU::constBool(bool val) {
	auto api = this;
	return WGCPUF_CONST(Bool, val);
}

WGA_Value *WorldGenAPI_CPU::constRule(WGA_Rule *val) {
	auto api = this;
	auto v = mapSymbol(val);
	return WGCPUF_CONST(Rule, v);
}

WGA_Value *WorldGenAPI_CPU::constComponentNode(WGA_ComponentNode *val) {
	auto api = this;
	auto v = mapSymbol(val);
	return WGCPUF_CONST(ComponentNode, v);
}

WGA_Biome *WorldGenAPI_CPU::newBiome() {
	WGA_Biome *biome = new WGA_Biome();
	symbols_ += biome;
	biomes_ += biome;
	return biome;
}

WGA_Rule *WorldGenAPI_CPU::newRule() {
	WGA_Rule *rule = new WGA_Rule();
	symbols_ += rule;
	return rule;
}

WGA_RuleExpansion *WorldGenAPI_CPU::newRuleExpansion(WGA_Rule *rule, WGA_Component *component, const QString &node) {
	WGA_RuleExpansion *ruleex = new WGA_RuleExpansion(rule, component, node);
	rule->addExpansion(ruleex);
	symbols_ += ruleex;
	return ruleex;
}

WGA_Component *WorldGenAPI_CPU::newComponent() {
	WGA_Component *component = new WGA_Component();
	symbols_ += component;
	return component;
}

WGA_ComponentNode *WorldGenAPI_CPU::newComponentNode() {
	WGA_ComponentNode *node = new WGA_ComponentNode();
	symbols_ += node;
	return node;
}

WGA_Value *WorldGenAPI_CPU::function(WorldGenAPI::FunctionID function, const WorldGenAPI::FunctionArgs &args) {
	return WGA_Funcs_CPU::functions()[function](this, args);
}

WGA_Value *WorldGenAPI_CPU::proxy(WGA_Value *v) {
	return registerSymbol(new WGA_Value_CPU(static_cast<WGA_Value_CPU *>(v)));
}

WGA_DataRecord_CPU::Ptr WorldGenAPI_CPU::getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor) {
	if(key.symbol->isContextual()) {
		ASSERT(structureGen);
		return structureGen->getDataRecord(key, ctor);
	}

	/*if(structureGen) {
		// We're requesting a value from structure gen -> mark it as crosssampled
		static_cast<WGA_Value_CPU*>(key.symbol)->markAsCrossSampled(key.subKey);
	}*/

	if(localCache) {
		// Qt6 - QHash references are no longer stable
		WGA_DataRecord_CPU::Ptr result = (*localCache)[key];
		if(!result) {
			result = dataCache_.get(key, ctor);
			(*localCache)[key] = result;
		}

		return result;
	}

	return dataCache_.get(key, ctor);
}

WGA_Biome &WorldGenAPI_CPU::getChunkBiome(const BlockWorldPos &origin_) {
	using Rec = WGA_DataRecordT_CPU<WGA_Biome *>;
	const BlockWorldPos origin = BlockWorldPos(origin_.x(), origin_.y(), 0);

	const auto ctor = [this](const WGA_DataRecord_CPU::Key &key) {
		QHash<WGA_Value_CPU *, float> fields;
		const auto getField = [&](WGA_Value_CPU *field) {
			if(fields.contains(field))
				return fields[field];

			const float result = WGA_ValueWrapper_CPU<ValueType::Float>(field).sampleAt(key.origin);
			fields[field] = result;
			return result;
		};

		float bestDeviation = std::numeric_limits<float>::max();
		WGA_Biome *bestBiome = nullptr;

		ASSERT(biomes_.size());
		for(WGA_Biome *biome: biomes_) {
			float deviation = biome->conditions().count() * -0.2f; // Give some advantage to biomes with many conditions
			for(const WGA_Biome::Condition &c: biome->conditions()) {
				const float fieldVal = getField(static_cast<WGA_Value_CPU *>(c.param));
				const float d = abs(c.mean - fieldVal) / c.deviation;
				deviation += pow(d, d > 1 ? 4 : 1);
			}

			if(deviation < bestDeviation) {
				bestBiome = biome;
				bestDeviation = deviation;
			}
		}

		auto r = new Rec();
		r->data = bestBiome;

		return WGA_DataRecord_CPU::Ptr(r);
	};

	auto rec = getDataRecord(WGA_DataRecord_CPU::Key(&chunkBiomeSymbol_, origin, 0), ctor);
	auto &r = static_cast<Rec &>(*rec);

	return *r.data;
}

QSharedPointer<WGA_DataRecordT_CPU<WGA_BiomeData_CPU>> WorldGenAPI_CPU::getBiomeData(const BlockWorldPos &origin_) {
	using Rec = WGA_DataRecordT_CPU<WGA_BiomeData_CPU>;
	const BlockWorldPos origin = BlockWorldPos(origin_.x(), origin_.y(), 0);

	const auto ctor = [this](const WGA_DataRecord_CPU::Key &key) {
		auto r = new Rec();

		r->data.calculateFor(*this, key.origin);

		return WGA_DataRecord_CPU::Ptr(r);
	};

	auto rec = getDataRecord(WGA_DataRecord_CPU::Key(&biomeDataSymbol_, origin, 0), ctor);
	auto r = rec.staticCast<Rec>();

	return r;
}

void WorldGenAPI_CPU::reportCacheHitRate() {
	dataCache_.reportHitRate();
}

WGA_Value *WorldGenAPI_CPU::grammarSymbolParam(WGA_GrammarSymbol *sym, const QString &name, WGA_Value::ValueType type,
                                               WGA_Value *defaultValue) {
	QSharedPointer<WGA_Value *> v(new WGA_Value *());
	const auto dimFunc = [v]() {
		ASSERT(structureGen);

		return structureGen->getInputParamDimensionality(*v);
	};
	const auto ctorFunc = [](const WGA_DataRecord_CPU::Key &) {
		throw;
		return WGA_DataCache_CPU::DataRecordPtr();
	};

	ASSERT(!defaultValue || defaultValue->valueType() == type);

	WGA_GrammarSymbol::ParamDeclare param;
	param.paramName = name;
	param.defaultValue = defaultValue;
	param.type = type;
	param.value = registerSymbol(new WGA_Value_CPU(*this, type, true, dimFunc, ctorFunc));

	*v = param.value;
	sym->declareParam(param);

	return param.value;
}

WGA_SymbolID_CPU WorldGenAPI_CPU::mapSymbol(WGA_Symbol *sym) {
	WGA_SymbolID_CPU &result = symbolIDMapping_[sym];
	if(result)
		return result;

	result = idSymbolMapping_.size();
	idSymbolMapping_[result] = sym;
	return result;
}

void WorldGenAPI_CPU::createLocalCache() {
	ASSERT(!localCache);
	localCache = new LocalCache();
}

void WorldGenAPI_CPU::destroyLocalCache() {
	ASSERT(localCache);
	delete localCache;
	localCache = nullptr;
}
