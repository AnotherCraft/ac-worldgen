#include "wglutils.h"

#include <unordered_map>
#include <regex>

#include "util/assert.h"
#include "util/enumutils.h"

WGLUtils::SymbolType WGLUtils::getSymbolType(const antlr4::Token *val) {
	static const std::unordered_map<std::string, SymbolType> tbl{
		{"namespace", SymbolType::Namespace},
		{"component", SymbolType::Component},
		{"rule",      SymbolType::Rule},
		{"biome",     SymbolType::Biome}
	};

	if(auto i = tbl.find(identifier(val)); i != tbl.end())
		return i->second;

	return SymbolType::Unknown;
}

const std::string &WGLUtils::getSymbolTypeName(WGLUtils::SymbolType t) {
	static std::unordered_map<int, std::string> data{
		{+SymbolType::Unknown,           "(unknown)"},
		{+SymbolType::Biome,             "biome"},
		{+SymbolType::BiomeParam,        "biome param"},
		{+SymbolType::Namespace,         "namespace"},
		{+SymbolType::Rule,              "structure rule"},
		{+SymbolType::RuleExpansion,     "structure rule expansion"},
		{+SymbolType::StructureParam,    "structure param"},
		{+SymbolType::Scope,             "scope"},
		{+SymbolType::Component,         "structure component"},
		{+SymbolType::ComponentNode,     "node"},
		{+SymbolType::FieldVariable,     "field variable"},
		{+SymbolType::StructureVariable, "local variable"},
	};

	ASSERT(data.contains(+t));
	return data[+t];
}

std::string WGLUtils::identifier(const antlr4::Token *id) {
	if(!id)
		return {};

	return id->getText();
}

float WGLUtils::numericLiteral(const antlr4::Token *val) {
	static const std::regex rx("[~#]");
	return std::stof(std::regex_replace(val->getText(), rx, ""));
}

std::string WGLUtils::stringLiteral(const antlr4::Token *val) {
	static const std::regex rx("[\"]");
	return std::regex_replace(val->getText(), rx, "");
}
