#pragma once

#include <vector>
#include <stack>
#include <list>

#include "util/matrix.h"
#include "util/blockorientation.h"

#include "worldgen/base/supp/wga_component.h"

#include "wga_datacache_cpu.h"
#include "wga_structureoutputdata_cpu.h"
#include "../worldgenapi_cpu.h"

class WGA_StructureGenerator_CPU {

public:
	using Seed = uint32_t;

	struct Area {
		int nameID; ///< using areaNameMapping
		BlockWorldPos startPos, endPos;
	};

	struct DataContext;
	using DataContextPtr = std::shared_ptr<DataContext>;

	struct DataContext {

	public:
		~DataContext();
		static DataContextPtr create(WorldGenAPI_CPU *api, const DataContextPtr &parentContext, WGA_GrammarSymbol *sym, const BlockTransformMatrix &transform = {});

	public:
		void setParams();

		inline WGA_GrammarSymbol *associatedSymbol() {
			return sym_;
		}

		inline BlockWorldPos constSamplePos() const {
			return localToWorldMatrix_ * BlockWorldPos(0);
		}

		inline Seed seed() const {
			return seed_;
		}

	public:
		inline BlockWorldPos mapToWorld(const BlockWorldPos &localPos) const {
			return BlockWorldPos(localToWorldMatrix_ * localPos);
		}

		inline BlockTransformMatrix &localToWorldMatrix() {
			return localToWorldMatrix_;
		}

	public:
		/// Used by WorldGenAPI_CPU for obtaining contextual symbols
		WGA_DataRecord_CPU::Ptr getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor);

		WGA_Value::Dimensionality getValueDimensionality(const WGA_Value *val);

		WGA_Value::Dimensionality getInputParamDimensionality(WGA_Symbol *symbol);

	private:
		DataContext() = default;

		void load(WorldGenAPI_CPU *api, const DataContextPtr &parentContext, WGA_GrammarSymbol *sym, const BlockTransformMatrix &transform);

	private:
		static std::string paramKey(const std::string &paramName, WGA_Value::ValueType type);

	private:
		WorldGenAPI_CPU *api_ = nullptr;
		WGA_GrammarSymbol *sym_ = nullptr;
		DataContextPtr parentContext_;

		BlockTransformMatrix localToWorldMatrix_;

	private:
		std::unordered_map<WGA_DataRecord_CPU::Key, WGA_DataRecord_CPU::Ptr> dataCache_;
		std::unordered_map<const WGA_Value *, WGA_Value::Dimensionality> dimensionalityCache_;

		/// List of all passed param inputs and outputs
		std::unordered_map<std::string, WGA_Value *> paramInputs_, paramOutputs_;

		/// Maps param utility as defined in the WGA_GrammarSymbol paramDeclares to param keys
		std::unordered_map<WGA_Symbol *, std::string> paramKeyMapping_;

		/// Temporary symbols, are deleted with the context
		std::vector<WGA_Symbol *> temporarySymbols_;

		std::unordered_map<WGA_Symbol *, WGA_Value::Dimensionality> inputParamDimensionalityCache_;

		Seed seed_ = 0;

	};
	friend struct DataContext;

	struct RuleExpansionContext {

	public:
		WGA_Rule *const rule = nullptr;
		const BlockOrientation orientation;

	public:
		/// List of all expansions the rule can expand to, in the order they should be attempted to be expanded
		std::vector<WGA_Rule::CompiledExpansion> possibleExpansions;

	public:
		const DataContextPtr ruleData;

	};
	using RuleExpansionContextPtr = std::shared_ptr<RuleExpansionContext>;

	struct RuleExpansionSuperState {

	public:
		const RuleExpansionContextPtr context;
		const size_t expansionIndex = -1; ///< ix in RuleExpansionContext::possibleExpansions

	public:
		struct Option {
			WGA_ComponentNode *node = nullptr;
			BlockOrientation orientation;
		};

		/// List of all nodes that should be attempted to be expanded
		std::vector<Option> possibleOptions;

	public:
		const DataContextPtr expansionData;

	};
	using RuleExpansionSuperStatePtr = std::shared_ptr<RuleExpansionSuperState>;

	struct RuleExpansionState {

	public:
		const RuleExpansionSuperStatePtr superState;

	public:
		const size_t optionIndex = -1; ///< ix in RuleExpansionSuperState::possibleOptions

	};
	using RuleExpansionStatePtr = std::shared_ptr<RuleExpansionState>;
	using RuleExpansionStateList = std::vector<RuleExpansionStatePtr>;

	struct ComponentExpansionState {

	public:
		const WGA_Component *component = nullptr;
		const WGA_ComponentNode *entryNode = nullptr;

	public:
		const DataContextPtr data;

	};
	using ComponentExpansionStatePtr = std::shared_ptr<ComponentExpansionState>;

	struct State {
		const size_t areaCount, componentExpansionCount, currentlyExpandedRuleIx;

		// We straight up copy the rule expansion list to the state so we can safely work with both depth first and breath first expansion (just shrinking the expansion list wouldn't work on depth first expansion)
		const RuleExpansionStateList ruleExpansions;

	};

public:
	WGA_StructureGenerator_CPU(WorldGenAPI_CPU &api);

public:
	void setup(WGA_Rule *entryRule, const BlockWorldPos &origin, Seed seed);
	bool process();
	WGA_StructureOutputData_CPUPtr generateOutput();

public:
	inline DataContext *currentDataContext() {
		return currentDataContext_.get();
	}

	/// Used by WorldGenAPI_CPU for obtaining contextual symbols
	WGA_DataRecord_CPU::Ptr getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor);

	WGA_Value::Dimensionality getValueDimensionality(const WGA_Value *val);

	WGA_Value::Dimensionality getInputParamDimensionality(WGA_Symbol *symbol);

private:
	void bind();
	void unbind();

private:
	/// Returns false when fails, does not call failBranch
	bool expandRule(WGA_Rule *rule, const BlockWorldPos &localOrigin, const BlockOrientation &orientation, const DataContextPtr &data);

	/// Returns true if the rule was truly expanded
	bool processExpansion(RuleExpansionState &res);

	/// Generates next expansion variant state. Returns false if you run out of states. null previousState -> generate first expansion
	/// One rule can be expanded into various expansions, each expansion can construct a component originating in multiple possible nodes
	RuleExpansionStatePtr nextRuleExpansionState(const RuleExpansionContextPtr &ctx, const RuleExpansionState *previousState);

private:
	void addBranch();
	void failBranch();

	bool checkConditions(WGA_GrammarSymbol *sym);

private:
	static BlockWorldPos blockPosValue(WGA_Value *val, const BlockWorldPos &samplePoint);
	static bool boolValue(WGA_Value *val, const BlockWorldPos &samplePoint);
	static BlockID blockValue(WGA_Value *val, const BlockWorldPos &samplePoint);

private:
	std::stack<State> stateStack_;
	std::vector<Area> areas_;
	std::vector<ComponentExpansionStatePtr> componentExpansions_;
	RuleExpansionStateList ruleExpansions_;
	size_t currentlyExpandedRuleIx_; ///< Index to ruleExpansion to the current rule being processed

private:
	size_t expansionCount_ = 0, maxExpansionCount_ = 16384; ///< Limits how many expansion attempts can be made
	size_t maxStackDepth_ = 4096;
	Seed seed_;
	std::unordered_map<std::string, int> areaNameMapping_; ///< Mapping are names to int to speed up comparison

private:
	DataContextPtr currentDataContext_;
	WorldGenAPI_CPU &api_;

};

