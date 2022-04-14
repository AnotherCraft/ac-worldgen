#include "wgldeclarationpass.h"

#include <QSet>

#include "wglsymbol.h"
#include "wglerror.h"

void WGLDeclarationPass::enterScope(WoglacParser::ScopeContext *ctx) {
	WGLSymbol *sym = nullptr;

	if(!ctx->extend) {
		WGLSymbol *target = lookupIdentifier(ctx->id, true);

		SymbolType type = WGLUtils::getSymbolType(ctx->type);

		if(type == SymbolType::Unknown)
			type = SymbolType::Scope;

		sym = new WGLSymbol(ctx_, target, ctx->id ? WGLUtils::identifier(ctx->id->id.back()) : QString(), type, ctx);
	}
	else {
		sym = lookupIdentifier(ctx->id, false);
		const WGLSymbol::Type targetType = WGLUtils::getSymbolType(ctx->type);

		if(sym->symbolType() != targetType)
			throw WGLError(
				QStringLiteral("Symbol extension target type mismatch: '%1' expected, but trying to extend as '%2'").arg(
					WGLUtils::getSymbolTypeName(sym->symbolType()), WGLUtils::getSymbolTypeName(targetType)), ctx);
	}

	currentScope_ += sym;
}

void WGLDeclarationPass::exitScope(WoglacParser::ScopeContext *ctx) {
	popScope(ctx);
}

void WGLDeclarationPass::enterRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) {
	WGLSymbol *directTarget = lookupIdentifier(ctx->target, false);
	WGLSymbol *effectiveTarget = directTarget->effectiveTarget();

	if(effectiveTarget->symbolType() != SymbolType::Rule)
		throw WGLError(QStringLiteral("Target '%1' for a rule expansion is not a rule.").arg(effectiveTarget->fullName()),
		               ctx);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, QString(), SymbolType::RuleExpansion, ctx);
	currentScope_ += sym;
}

void WGLDeclarationPass::exitRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) {
	popScope(ctx);
}

void WGLDeclarationPass::enterParamDefinition(WoglacParser::ParamDefinitionContext *ctx) {
	static const QSet<int> allowedTargets{
		+SymbolType::Rule, +SymbolType::RuleExpansion, +SymbolType::Component
	};

	WGLSymbol *directTarget = lookupIdentifier(ctx->target, false);
	WGLSymbol *effectiveTarget = directTarget->effectiveTarget();

	checkTargetTypeMatch(ctx->targetType, effectiveTarget, ctx);

	if(!allowedTargets.contains(+effectiveTarget->symbolType()))
		throw WGLError(
			QStringLiteral("Target '%1': symbol type '%2' cannot have local params.").arg(effectiveTarget->fullName(), WGLUtils::getSymbolTypeName(effectiveTarget->symbolType())), ctx);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, WGLUtils::identifier(ctx->id), SymbolType::StructureParam, ctx);
	sym->valueType = WGA_Value::typesByName[WGLUtils::identifier(ctx->type)];
}

void WGLDeclarationPass::enterBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext *ctx) {
	WGLSymbol *directTarget = lookupIdentifier(ctx->id, true);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, WGLUtils::identifier(ctx->id->id.back()), SymbolType::BiomeParam, ctx);
	sym->valueType = WGA_Value::typesByName[WGLUtils::identifier(ctx->type)];
}

void WGLDeclarationPass::enterVariableDefinition(WoglacParser::VariableDefinitionContext *ctx) {
	static const QHash<int, SymbolType> varSymbolTypeFromTargetType{
		{+SymbolType::Biome,         SymbolType::FieldVariable},
		{+SymbolType::Namespace,     SymbolType::FieldVariable},
		{+SymbolType::Rule,          SymbolType::StructureVariable},
		{+SymbolType::RuleExpansion, SymbolType::StructureVariable},
		{+SymbolType::Component,     SymbolType::StructureVariable}
	};

	WGLSymbol *directTarget = lookupIdentifier(ctx->id, true);
	WGLSymbol *effectiveTarget = directTarget->effectiveTarget();

	const SymbolType symbolType = varSymbolTypeFromTargetType.value(+effectiveTarget->symbolType());
	if(symbolType == SymbolType::Unknown)
		throw WGLError(QStringLiteral("Variables are not allowed inside '%1'.").arg(
			WGLUtils::getSymbolTypeName(effectiveTarget->symbolType())), ctx);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, WGLUtils::identifier(ctx->id->id.back()), symbolType, ctx);
	sym->isExport = ctx->exportFlag;
	sym->valueType = WGA_Value::typesByName[WGLUtils::identifier(ctx->type)];
}

void WGLDeclarationPass::enterComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) {
	WGLSymbol *sym = componentNodeDeclaration(ctx->cmn, currentScope());
	currentScope_ += sym;
}

void WGLDeclarationPass::exitComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) {
	popScope(ctx->cmn);
}

void WGLDeclarationPass::enterComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) {
	WGLSymbol *directTarget = currentScope();
	WGLSymbol *effectiveTarget = directTarget->effectiveTarget();

	if(effectiveTarget->symbolType() != SymbolType::Component)
		throw WGLError("Component include can only be used in a component symbol.", ctx);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, QString(), SymbolType::Scope, ctx);
	currentScope_ += sym;
}

void WGLDeclarationPass::exitComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) {
	popScope(ctx);
}
