#include "worldgenapi.h"

#include <iostream>
#include <cmath>
#include <set>
#include <format>

#include "util/iterators.h"

#include <iostream>

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
