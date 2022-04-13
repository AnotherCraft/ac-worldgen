#include "wglpass.h"

#include "wglerror.h"

WGLPass::WGLPass() {
	currentScope_ += nullptr;
}

void WGLPass::setContext(WGLContext *ctx) {
	ctx_ = ctx;
}

void WGLPass::execute(WoglacParser::ModuleContext *module) {
	ASSERT(currentScope_.size() == 1);

	currentScope_[0] = ctx_->rootSymbol;
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
	for(int i = currentScope_.size() - 1; i >= 0; i--) {
		if((result = currentScope_[i]->resolveIdentifier(baseId, eid, false)))
			break;
	}

	if(!result)
		throw WGLError(
			QStringLiteral("Failed to lookup identifier '%1' in scope '%2'.").arg(QString::fromStdString(baseId->getText()),
			                                                                      currentScope()->fullName()), eid);

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
		throw WGLError(QStringLiteral("Specified target type '%1' doesn't match with target symbol '%2' type '%3'.").arg(
			WGLUtils::getSymbolTypeName(tt), effectiveTarget->fullName(),
			WGLUtils::getSymbolTypeName(effectiveTarget->symbolType())), ctx);
}

void WGLPass::popScope(antlr4::ParserRuleContext *ctx) {
	ASSERT(ctx_->astSymbolMapping.contains(ctx));
	ASSERT(ctx_->astSymbolMapping.value(ctx) == currentScope_.top());

	currentScope_.pop();
}

WGLSymbol *
WGLPass::componentNodeDeclaration(WoglacParser::ComponentNodeStatementCommonPartContext *ctx, WGLSymbol *directTarget,
                                  bool useDeclarationAST) {
	WGLSymbol *effectiveTarget = directTarget->effectiveTarget();

	if(effectiveTarget->symbolType() != SymbolType::Component)
		throw WGLError("Nodes cannot be defined outside structure components.", ctx);

	const QString baseName = WGLUtils::identifier(ctx->group);
	QString name = baseName;
	int i = 2;
	while(!name.isEmpty() && directTarget->childrenByName().contains(name))
		name = QStringLiteral("%1_%2").arg(baseName, QString::number(i++));

	return new WGLSymbol(ctx_, directTarget, name, SymbolType::ComponentNode, useDeclarationAST ? ctx : nullptr);
}
