#include "wga_component.h"

#include "wga_componentnode.h"

WGA_Component::WGA_Component() {
	setDescription("(component)");

	static const PragmaList pg{
		{"allowMirroring", false},
	};
	pragmas_ = pg;
}

WGA_Symbol::SymbolType WGA_Component::symbolType() const {
	return SymbolType::Component;
}

void WGA_Component::addNode(WGA_ComponentNode *node) {
	node->setParentComponent(this);
	nodesByGroup_[node->config().group].push_back(node);
	nodes_.push_back(node);
}

void WGA_Component::addArea(const WGA_Component::Area &area) {
	ASSERT(area.startPos);
	ASSERT(area.endPos);

	ASSERT(area.startPos->valueType() == WGA_Value::ValueType::Float3);
	ASSERT(area.endPos->valueType() == WGA_Value::ValueType::Float3);

	areas_.push_back(area);
}

void WGA_Component::addBlocks(const WGA_Component::Blocks &area) {
	ASSERT(area.block);

	ASSERT(!area.startPos || area.startPos->valueType() == WGA_Value::ValueType::Float3);
	ASSERT(!area.endPos || area.endPos->valueType() == WGA_Value::ValueType::Float3);
	ASSERT(area.startPos || !area.endPos);

	blockAreas_.push_back(area);
}
