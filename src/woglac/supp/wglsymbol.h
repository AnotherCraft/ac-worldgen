#pragma once

#include <string>

#include "wglinclude.h"

#include "worldgen/base/supp/wga_value.h"

#include "wglutils.h"

class WGLContext;

class WGLSymbol {

public:
	friend class WGLContext;

	using Type = WGLUtils::SymbolType;

public:
	WGLSymbol(WGLContext *context, WGLSymbol *parent, const std::string &name, Type type, antlr4::ParserRuleContext *declarationContext);

public:
	inline const std::string &name() const {
		return name_;
	}

	// Fully identified name (parentFullName.name)
	inline const std::string &fullName() const {
		return fullName_;
	}

	/// Description - name, file, line, ...
	inline const std::string &desc() const {
		return desc_;
	}

	inline Type symbolType() const {
		return type_;
	}

	/// Direct parent of the symbol
	inline WGLSymbol *parent() {
		return parent_;
	}

	/// Effective target -> if the symbol is a scope, returns its parent's effective target
	inline WGLSymbol *effectiveTarget() {
		return effectiveTarget_;
	}

	inline const auto &childrenByName() {
		return childrenByName_;
	}

public:
	WGA_Value::ValueType valueType = WGA_Value::ValueType::Undefined;
	bool isExport = false;

public:
	/// Looks for the identifier in the current scope only
	WGLSymbol *resolveIdentifier(const antlr4::Token *id, antlr4::ParserRuleContext *ctx, bool throwError);
	WGLSymbol *resolveIdentifier(const std::string &id, antlr4::ParserRuleContext *ctx, bool throwError);

private:
	~WGLSymbol();

private:
	WGLContext &context_;
	WGLSymbol *parent_ = nullptr, *effectiveTarget_ = nullptr;
	std::string name_, fullName_, desc_;
	Type type_;
	std::vector<WGLSymbol *> children_;
	std::unordered_map<std::string, WGLSymbol *> childrenByName_;
	antlr4::ParserRuleContext *declarationAst_;

};

