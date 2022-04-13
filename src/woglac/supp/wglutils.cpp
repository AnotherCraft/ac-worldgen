#include "wglutils.h"

#include <QHash>

#include "util/assert.h"
#include "util/enumutils.h"

WGLUtils::SymbolType WGLUtils::getSymbolType(const antlr4::Token *val) {
	static const QHash<QString, SymbolType> tbl{
		{"namespace", SymbolType::Namespace},
		{"component", SymbolType::Component},
		{"rule",      SymbolType::Rule},
		{"biome",     SymbolType::Biome}
	};

	return tbl.value(identifier(val), SymbolType::Unknown);
}

const QString &WGLUtils::getSymbolTypeName(WGLUtils::SymbolType t) {
	static QHash<int, QString> data{
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

QString WGLUtils::identifier(const antlr4::Token *id) {
	if(!id)
		return QString();

	return QString::fromStdString(id->getText());
}

float WGLUtils::numericLiteral(const antlr4::Token *val) {
	return QString::fromStdString(val->getText()).remove('~').remove('#').toFloat();
}

QString WGLUtils::stringLiteral(const antlr4::Token *val) {
	return QString::fromStdString(val->getText()).remove('"');
}
