#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <map>

#include "wga_grammarsymbol.h"
#include "wga_value.h"

class WGA_Component : public WGA_GrammarSymbol {

public:
	/// Areas are used for ensuring that various structures do not overlap
	struct Area {
		std::string name;
		WGA_Value *startPos = nullptr; ///< Component-local position
		WGA_Value *endPos = nullptr; ///< Component-local position

		bool canOverlap = false; ///< If true, the area can overlap other areas
		bool mustOverlap = false; ///< If true, the area is REQUIRED to overlap other areas
		bool isVirtual = false; ///< If true, the area is only used for checking against other areas, but is not actually generated
	};

	/// Area of parametrically defined blocks
	struct Blocks {
		WGA_Value *startPos = nullptr; ///< Component-local position
		WGA_Value *endPos = nullptr; ///< Component-local position, can be null

		std::vector<BlockWorldPos> positions; ///< Alternative to startPos/endPos
		WGA_Value *positionsOffset = nullptr; ///< Offset to positions

		WGA_Value *block = nullptr;
	};

public:
	WGA_Component();

public:
	virtual SymbolType symbolType() const override;

public:
	inline const auto nodes(const std::string &name) const {
		if(auto r = nodesByGroup_.find(name); r != nodesByGroup_.end())
			return r->second;

		return std::vector<WGA_ComponentNode *>{};
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
	std::unordered_map<std::string, std::vector<WGA_ComponentNode *>> nodesByGroup_;
	std::vector<WGA_ComponentNode *> nodes_;
	std::vector<Area> areas_;
	std::vector<Blocks> blockAreas_;

};

