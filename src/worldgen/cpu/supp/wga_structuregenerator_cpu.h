#pragma once

#include <vector>
#include <stack>

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
	struct State {
		int areaCount, componentExpansionCount, ruleExpansionCount, currentlyExpandedRuleIx;
	};
	struct DataContext {

	public:
		~DataContext();

	public:
		void load(WorldGenAPI_CPU *api, DataContext *parentContext, WGA_GrammarSymbol *sym);
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
		static std::string paramKey(const std::string &paramName, WGA_Value::ValueType type);

	private:
		WorldGenAPI_CPU *api_ = nullptr;
		WGA_GrammarSymbol *sym_ = nullptr;
		DataContext *parentContext_ = nullptr;

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
	struct RuleExpansionNode {
		WGA_ComponentNode *node;
		BlockOrientation orientation;
	};

	struct RuleExpansionState {

	public:
		DataContext ruleData;
		WGA_Rule *rule = nullptr;
		BlockOrientation orientation;

	public:
		DataContext currentExpansionData;
		std::vector<WGA_Rule::CompiledExpansion> possibleExpansions;
		std::vector<RuleExpansionNode> possibleExpansionNodes;
		int currentExpansionIndex = -1;
		int currentExpansionNodeIndex = -1;

	};
	using RuleExpansionStatePtr = std::shared_ptr<RuleExpansionState>;

	struct ComponentExpansionState {

	public:
		DataContext data;
		WGA_Component *component = nullptr;
		WGA_ComponentNode *entryNode = nullptr;

		/// Hash incorporates component type and transform matrix
		size_t placementHash = 0;

	};
	using ComponentExpansionStatePtr = std::shared_ptr<ComponentExpansionState>;

public:
	WGA_StructureGenerator_CPU(WorldGenAPI_CPU &api);

public:
	void setup(WGA_Rule *entryRule, const BlockWorldPos &origin, Seed seed);
	bool process();
	WGA_StructureOutputData_CPUPtr generateOutput();

public:
	inline DataContext *currentDataContext() {
		return currentDataContext_;
	}

	/// Used by WorldGenAPI_CPU for obtaining contextual symbols
	WGA_DataRecord_CPU::Ptr getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor);

	WGA_Value::Dimensionality getValueDimensionality(const WGA_Value *val);

	WGA_Value::Dimensionality getInputParamDimensionality(WGA_Symbol *symbol);

private:
	void bind();
	void unbind();

private:
	/// Returns false on failBranch
	bool expandRule(WGA_Rule *rule, const BlockWorldPos &localOrigin, const BlockOrientation &orientation, DataContext *data);

	/// Returns true if the rule was truly expanded
	bool processExpansion(RuleExpansionState &res);

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
	std::vector<RuleExpansionStatePtr> ruleExpansions_;
	int currentlyExpandedRuleIx_ = -1; ///< Index to ruleExpansion to the current rule being processed

private:
	int expansionCount_ = 0, maxExpansionCount_ = 16384; ///< Limits how many expansion attempts can be made
	int maxStackDepth_ = 512;
	Seed seed_;
	std::unordered_map<std::string, int> areaNameMapping_; ///< Mapping are names to int to speed up comparison

private:
	DataContext *currentDataContext_ = nullptr;
	WorldGenAPI_CPU &api_;

};

