#pragma once

#include <QString>
#include <QVariant>
#include <QHash>

class WGA_Symbol {

public:
	using PragmaList = QHash<QString, QVariant>;
	enum class SymbolType {
		Abstract,
		Value,
		Biome,
		Component,
		Rule,
		RuleExpansion,
		StructureNode,
	};

public:
	WGA_Symbol();
	virtual ~WGA_Symbol();

public:
	virtual SymbolType symbolType() const;

	/// If true, the value is local to a structure/grammar symbol instance
	virtual bool isContextual() const;

public:
	QVariant pragma(const QString &name) const;

	inline const auto &pragmas() const {
		return pragmas_;
	}

	void setPragma(const QString &name, const QVariant &value = true);
	void setPragmas(const PragmaList &pragmas);

public:
	inline const QString &description() const {
		return desc_;
	}

	inline void setDestription(const QString &set) {
		desc_ = set;
	}

protected:
	PragmaList pragmas_;

private:
	QString desc_;

};

