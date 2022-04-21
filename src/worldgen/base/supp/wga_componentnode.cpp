#include "wga_componentnode.h"

WGA_ComponentNode::WGA_ComponentNode() {
	setDescription("(componentNode)");

	static const PragmaList pg{
		{"allowRotation",  false},
		{"horizontalEdge", false},
		{"verticalEdge",   false},
		{"adjacent",       true}
	};
	pragmas_ = pg;
}

WGA_Symbol::SymbolType WGA_ComponentNode::symbolType() const {
	return SymbolType::StructureNode;
}

void WGA_ComponentNode::setConfig(const WGA_ComponentNode::Config &set) {
	config_ = set;

	setPragma("allowRotation", config_.orientation.isVertical());
}

void WGA_ComponentNode::setParentComponent(WGA_Component *set) {
	ASSERT(!parentComponent_);
	ASSERT(set);

	parentComponent_ = set;
}
