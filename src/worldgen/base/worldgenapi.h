#pragma once

#include <functional>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "supp/wga_value.h"
#include "supp/wga_biome.h"
#include "supp/wga_grammarsymbol.h"
#include "supp/wga_rule.h"
#include "supp/wga_ruleexpansion.h"
#include "supp/wga_component.h"

class WorldGenAPI {

public:
	using Seed = uint32_t;
	using FunctionArgs = std::vector<WGA_Value *>;
	using FunctionID = int;
	using Type = WGA_Value::ValueType;

public:
	struct FunctionArgument {

	public:
		FunctionArgument() {}

		inline FunctionArgument(Type type, const std::string &name) : type(type), name(name) {}

	public:
		Type type;
		std::string name;

	};
	struct Function {

	public:
		/// Integer ID
		FunctionID id;

		/// Name of the function
		std::string name;

		/// name(Arg1, Arg2, ...)
		std::string prototype;

		/// For documentation purposes
		std::string description;

		std::string section;

	public:
		std::vector<FunctionArgument> arguments;
		FunctionArgument returnValue;

	public:
		static std::string composePrototype(const std::string &functionName, const std::vector<WGA_Value::ValueType> &argTypes);

	};
	struct Functions {

	public:
		std::vector<Function> list;
		std::map<std::string, FunctionID> prototypeMapping;
		std::unordered_set<std::string> nameSet;
		std::vector<std::string> nameList; ///< Ordered name list
		std::map<std::string, std::vector<FunctionID>> nameMapping;

	public:
		/// Generates documentation in markdown format
		void generateDocumentation() const;

	};
	static const Functions &functions();

public:
	virtual ~WorldGenAPI();

public:
	inline WorldGenSeed seed() const {
		return seed_;
	}

	virtual void setSeed(WorldGenSeed set) {
		seed_ = set;
	}

	inline const std::unordered_map<std::string, BlockID> &blockUIDMapping() const {
		return blockUIDMapping_;
	}

	virtual void setBlockUIDMapping(const std::unordered_map<std::string, BlockID> &set) {
		blockUIDMapping_ = set;
	}

	inline auto biomeGridSize() const {
		return biomeGridSize_;
	}

	inline void setBiomeGridSize(BlockWorldPos_T set) {
		if(set < 16 || !std::has_single_bit(static_cast<uint64_t>(set)))
			throw std::exception("Biome grid size must be larger than 16 and be power of 2.");

		biomeGridSize_ = set;
	}

public:
	virtual WGA_Value *constFloat(float val) = 0;
	virtual WGA_Value *constFloat3(const V3F val) = 0;
	virtual WGA_Value *constBlock(BlockID val) = 0;
	virtual WGA_Value *constBool(bool val) = 0;
	virtual WGA_Value *constRule(WGA_Rule *val) = 0;
	virtual WGA_Value *constComponentNode(WGA_ComponentNode *val) = 0;

	inline WGA_Value *airBlock() {
		return constBlock(BlockID(0));
	}

	inline WGA_Value *constBlock(const std::string &uid) {
		const auto r = blockUIDMapping_.find(uid);
		if(r == blockUIDMapping_.end())
			throw std::exception(std::format("Block UID '{}' not defined.", uid).c_str());

		return constBlock(r->second);
	}

public:
	virtual WGA_Biome *newBiome() = 0;
	virtual WGA_Rule *newRule() = 0;

	/// New rule expansion that expands to nothing
	virtual WGA_RuleExpansion *newRuleExpansion(WGA_Rule *rule) = 0;

	/// Rule expansion to a component
	virtual WGA_RuleExpansion *newRuleExpansion(WGA_Rule *rule, WGA_Component *component, const std::string &node) = 0;

	/// Rule expansion to another rule
	virtual WGA_RuleExpansion *newRuleExpansion(WGA_Rule *rule, WGA_Rule *targetRule) = 0;

	virtual WGA_Component *newComponent() = 0;
	virtual WGA_ComponentNode *newComponentNode() = 0;

public:
	virtual WGA_Value *function(FunctionID function, const FunctionArgs &args) = 0;

	/// Proxy creates a WGA_Value with exact same values as #v.
	/// This is useful for biome variables, because they are indexed by the default WGA_Value.
	/// So if the default value is same for multiple biome variables, they would be considered the same one variable. Creating a proxy prevents that.
	virtual WGA_Value *proxy(WGA_Value *v) = 0;

	/// Returns value representing given grammar symbol param.
	virtual WGA_Value *grammarSymbolParam(WGA_GrammarSymbol *sym, const std::string &name, WGA_Value::ValueType type, WGA_Value *defaultValue) = 0;

private:
	WorldGenSeed seed_ = 0;
	std::unordered_map<std::string, BlockID> blockUIDMapping_;
	BlockWorldPos_T biomeGridSize_ = 256;

};

