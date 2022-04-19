#include "worldgenapi.h"

#include <iostream>
#include <cmath>
#include <set>
#include <format>

#include "util/iterators.h"
#include "util/macroutils.h"

const WorldGenAPI::Functions &WorldGenAPI::functions() {
	static const Functions fs = [] {
		Functions fs;
		Function f;

		const auto finalize = [&]() {
			f.prototype = Function::composePrototype(f.name, iterator(f.arguments).mapx(x.type).toList());
			f.id = fs.list.size();
			fs.list.push_back(f);
			fs.prototypeMapping[f.prototype] = f.id;
			if(!fs.nameSet.contains(f.name))
				fs.nameList.push_back(f.name);
			fs.nameSet.insert(f.name);
			fs.nameMapping[f.name].push_back(f.id);
		};

#include "worldgen/util/wg_macro_def.h"

#undef SECTION
#define SECTION(name) f.section = name;

#define ARGS_END(returnType) \
  DEFER2(CONCAT)(RET_, M_ARG_1 returnType)(PREVENT_EATING_COMMA(M_ARG_1_REST returnType)) \
  finalize();

#define ARG_ARG(name, ai, i, Rest) \
  f.arguments[i-1] = FunctionArgument(f.arguments[ai-1].type, #name); \
  Rest
#define ARG_T(name, T, i, Rest) \
  f.arguments[i-1] = FunctionArgument(Type::T, #name); \
  Rest

#define RET_T(name, T) f.returnValue = FunctionArgument(Type::T, #name);
#define RET_ARG(name, i) f.returnValue = FunctionArgument(f.arguments[i-1].type, #name);

#define ARG_APPLY(arg, i, Rest) DEFER2(CONCAT)(ARG_, M_ARG_1 arg)(PREVENT_EATING_COMMA(M_ARG_1_REST arg), i, DEFER8(Rest))
#define FUNC(funcName, argCount, args, returnType, dim, impl, desc, ...) \
  f.name = #funcName; \
  f.arguments.resize(argCount); \
  f.description = desc; \
  DEFER(ARGS_ ## argCount)(DEFER(DEFER args), returnType)

		WORLDGEN_FUNCTIONS

#include "worldgen/util/wg_macro_undef.h"

		return fs;
	}();
	return fs;
}

WorldGenAPI::~WorldGenAPI() {

}

std::string WorldGenAPI::Function::composePrototype(const std::string &functionName, const std::vector<WGA_Value::ValueType> &argTypes) {
	return std::format("{}({})", functionName, iterator(argTypes).mapx(WGA_Value::typeNames.at(x)).join(", "));
}

void WorldGenAPI::Functions::generateDocumentation() const {
	const WorldGenAPI::Functions &functions = WorldGenAPI::functions();

	std::string section;

	for(const std::string &fn: functions.nameList) {
		const std::string s = list[functions.nameMapping.at(fn)[0]].section;
		if(section != s) {
			section = s;
			std::cout << "# " << s << "\n\n";
		}

		std::cout << "## `" << fn << "` \n";

		std::unordered_map<std::string, std::string> prototypesByDescription;
		std::set<std::string> mentionedPrototypes;

		for(const WorldGenAPI::FunctionID fid: functions.nameMapping.at(fn)) {
			const WorldGenAPI::Function &f = functions.list[fid];
			const std::string prototype = std::format("{} {}({})\n",
			                                          WGA_Value::typeNames.at(f.returnValue.type),
			                                          f.name,
			                                          iterator(f.arguments).mapx(std::format("{} {}", WGA_Value::typeNames.at(x.type), x.name)).join(", ")
			);

			if(mentionedPrototypes.contains(prototype))
				continue;

			mentionedPrototypes.insert(prototype);
			prototypesByDescription[f.description] += prototype;
		}

		for(auto it = prototypesByDescription.begin(), end = prototypesByDescription.end(); it != end; it++) {
			std::cout << "```WOGLAC\n";
			std::cout << it->second; // Prototypes
			std::cout << "```\n";

			std::cout << "\n";
			std::cout << it->first; // Description
			std::cout << "\n";
		}
	}
}
