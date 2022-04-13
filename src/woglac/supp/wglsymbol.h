#pragma once

// Must place before everything else because of antlr
#include "wglinclude.h"

#include <QString>
#include <QList>
#include <QHash>

#include "worldgen/base/supp/wga_value.h"

#include "wglutils.h"

class WGLContext;

class WGLSymbol {

public:
	friend class WGLContext;

	using Type = WGLUtils::SymbolType;

public:
	WGLSymbol(WGLContext *context, WGLSymbol *parent, const QString &name, Type type,
	          antlr4::ParserRuleContext *declarationContext);

public:
	inline const QString &name() const {
		return name_;
	}

	// Fully identified name (parentFullName.name)
	inline const QString &fullName() const {
		return fullName_;
	}

	/// Description - name, file, line, ...
	inline const QString &desc() const {
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

public:
	/// Looks for the identifier in the current scope only
	WGLSymbol *resolveIdentifier(const antlr4::Token *id, antlr4::ParserRuleContext *ctx, bool throwError);
	WGLSymbol *resolveIdentifier(const QString &id, antlr4::ParserRuleContext *ctx, bool throwError);

private:
	~WGLSymbol();

private:
	WGLContext &context_;
	WGLSymbol *parent_ = nullptr, *effectiveTarget_ = nullptr;
	QString name_, fullName_, desc_;
	Type type_;
	QVector<WGLSymbol *> children_;
	QHash<QString, WGLSymbol *> childrenByName_;
	antlr4::ParserRuleContext *declarationAst_;

};

