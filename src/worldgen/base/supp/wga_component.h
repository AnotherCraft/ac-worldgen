#pragma once

#include <QString>

#include "wga_grammarsymbol.h"
#include "wga_value.h"

class WGA_Component : public WGA_GrammarSymbol {

public:
	/// Areas are used for ensuring that various structures do not overlap
	struct Area {
		QString name;
		WGA_Value *startPos = nullptr; ///< Component-local position
		WGA_Value *endPos = nullptr; ///< Component-local position
	};

	/// Area of parametrically defined blocks
	struct Blocks {
		WGA_Value *startPos = nullptr; ///< Component-local position
		WGA_Value *endPos = nullptr; ///< Component-local position, can be null
		QVector<BlockWorldPos> positions; ///< Alternative to startPos/endPos

		WGA_Value *block = nullptr;
	};

public:
	WGA_Component();

public:
	virtual SymbolType symbolType() const override;

public:
	inline const auto nodes(const QString &name) const {
		return nodesByGroup_.value(name);
	}

	inline const auto &nodes() const {
		return nodes_;
	}

	void addNode(WGA_ComponentNode *node);

	inline const auto &areas() const {
		return areas_;
	}

	void addArea(const Area &area);

	inline const auto &blockAreas() const {
		return blockAreas_;
	}

	void addBlocks(const Blocks &area);

private:
	QHash<QString, QVector<WGA_ComponentNode *>> nodesByGroup_;
	QVector<WGA_ComponentNode *> nodes_;
	QList<Area> areas_;
	QList<Blocks> blockAreas_;

};

