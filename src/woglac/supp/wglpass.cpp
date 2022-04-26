#include "wglpass.h"

#include "wglerror.h"

WGLPass::WGLPass() {
	currentScope_.push(nullptr);
}

void WGLPass::setContext(WGLContext *ctx) {
	ctx_ = ctx;
}

void WGLPass::execute(WoglacParser::ModuleContext *module) {
	ASSERT(currentScope_.size() == 1);

	currentScope_.top() = ctx_->rootSymbol;
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(this, module);

	ASSERT(currentScope_.size() == 1);
}

WGLSymbol *WGLPass::lookupIdentifier(WoglacParser::ExtendedIdentifierContext *eid, bool skipLast) {
	// Null target -> returns the current symbol
	if(!eid || eid->id.size() <= static_cast<size_t>(skipLast))
		return currentScope();

	auto it = eid->id.begin();
	const antlr4::Token *baseId = *it++;

	WGLSymbol *result = nullptr;
	auto scope = currentScope_;
	while(!scope.empty()) {
		if((result = scope.top()->resolveIdentifier(baseId, eid, false)))
			break;

		scope.pop();
	}

	if(!result)
		throw WGLError(std::format("Failed to lookup identifier '{}' in scope '{}'.", baseId->getText(), currentScope()->fullName()), eid);

	auto end = eid->id.end();
	if(skipLast)
		end--;

	for(; it != end; it++)
		result = result->resolveIdentifier(*it, eid, true);

	return result;
}

void
WGLPass::checkTargetTypeMatch(antlr4::Token *targetType, WGLSymbol *effectiveTarget, antlr4::ParserRuleContext *ctx) {
	if(!targetType)
		return;

	SymbolType tt = WGLUtils::getSymbolType(targetType);

	if(tt != effectiveTarget->symbolType())
		throw WGLError(std::format("Specified target type '{}' doesn't match with target symbol '{}' type '{}'.", WGLUtils::getSymbolTypeName(tt), effectiveTarget->fullName(), WGLUtils::getSymbolTypeName(effectiveTarget->symbolType())), ctx);
}

void WGLPass::popScope(antlr4::ParserRuleContext *ctx) {
	ASSERT(ctx_->astSymbolMapping.contains(ctx));
	ASSERT(ctx_->astSymbolMapping.at(ctx) == currentScope_.top());

	currentScope_.pop();
}

WGLSymbol *WGLPass::componentNodeDeclaration(WoglacParser::ComponentNodeStatementCommonPartContext *ctx, WGLSymbol *directTarget, bool useDeclarationAST) {
	WGLSymbol *effectiveTarget = directTarget->effectiveTarget();

	if(effectiveTarget->symbolType() != SymbolType::Component)
		throw WGLError("Nodes cannot be defined outside structure components.", ctx);

	const std::string baseName = WGLUtils::identifier(ctx->group);
	std::string name = baseName;
	int i = 2;
	while(!name.empty() && directTarget->childrenByName().contains(name))
		name = std::format("{}_{}", baseName, std::to_string(i++));

	return new WGLSymbol(ctx_, directTarget, name, SymbolType::ComponentNode, useDeclarationAST ? ctx : nullptr);
}
