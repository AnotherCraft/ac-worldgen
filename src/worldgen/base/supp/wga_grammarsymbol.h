#pragma once

#include <QString>
#include <QVariant>

#include "wga_symbol.h"
#include "wga_value.h"

class WGA_GrammarSymbol : public WGA_Symbol {

public:
	struct ParamSet {
		QString paramName;
		WGA_Value *value = nullptr;
	};
	struct ParamDeclare {
		QString paramName;
		WGA_Value::ValueType type = WGA_Value::ValueType::Undefined;
		WGA_Value *value = nullptr;
		WGA_Value *defaultValue = nullptr;
	};
	struct Condition {
		WGA_Value *value = nullptr;
	};

public:
	WGA_GrammarSymbol();

public:
	void setParam(const QString &param, WGA_Value *value);

	inline const auto &paramSets() const {
		return paramSets_;
	}

	/// This function is to be called from the WorldGenAPI::grammarSymbolParam internally
	void declareParam(const ParamDeclare &param);

	inline const auto &paramDeclares() const {
		return paramDeclares_;
	}

	const inline auto &conditions() const {
		return conditions_;
	}

	void addCondition(const Condition &cond);

private:
	QList<Condition> conditions_;
	QList<ParamSet> paramSets_;
	QList<ParamDeclare> paramDeclares_;
	QHash<QString, QVariant> setPragmas_;

};

