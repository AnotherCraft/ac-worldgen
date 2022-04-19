#include "wgldeclarationpass.h"

#include <format>

#include "wglsymbol.h"
#include "wglerror.h"

void WGLDeclarationPass::enterScope(WoglacParser::ScopeContext *ctx) {
	WGLSymbol *sym = nullptr;

	if(!ctx->extend) {
		WGLSymbol *target = lookupIdentifier(ctx->id, true);

		SymbolType type = WGLUtils::getSymbolType(ctx->type);

		if(type == SymbolType::Unknown)
			type = SymbolType::Scope;

		sym = new WGLSymbol(ctx_, target, ctx->id ? WGLUtils::identifier(ctx->id->id.back()) : std::string{}, type, ctx);
	}
	else {
		sym = lookupIdentifier(ctx->id, false);
		const WGLSymbol::Type targetType = WGLUtils::getSymbolType(ctx->type);

		if(sym->symbolType() != targetType)
			throw WGLError(std::format("Symbol extension target type mismatch: '{}' expected, but trying to extend as '{}'", WGLUtils::getSymbolTypeName(sym->symbolType()), WGLUtils::getSymbolTypeName(targetType)), ctx);
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
		throw WGLError(std::format("Target '{}' for a rule expansion is not a rule.", effectiveTarget->fullName()), ctx);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, {}, SymbolType::RuleExpansion, ctx);
	currentScope_ += sym;
}

void WGLDeclarationPass::exitRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) {
	popScope(ctx);
}

void WGLDeclarationPass::enterParamDefinition(WoglacParser::ParamDefinitionContext *ctx) {
	static const std::unordered_set<int> allowedTargets{
		+SymbolType::Rule, +SymbolType::RuleExpansion, +SymbolType::Component
	};

	WGLSymbol *directTarget = lookupIdentifier(ctx->target, false);
	WGLSymbol *effectiveTarget = directTarget->effectiveTarget();

	checkTargetTypeMatch(ctx->targetType, effectiveTarget, ctx);

	if(!allowedTargets.contains(+effectiveTarget->symbolType()))
		throw WGLError(std::format("Target '{}': symbol type '{}' cannot have local params.", effectiveTarget->fullName(), WGLUtils::getSymbolTypeName(effectiveTarget->symbolType())), ctx);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, WGLUtils::identifier(ctx->id), SymbolType::StructureParam, ctx);
	sym->valueType = WGA_Value::typesByName.at(WGLUtils::identifier(ctx->type));
}

void WGLDeclarationPass::enterBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext *ctx) {
	WGLSymbol *directTarget = lookupIdentifier(ctx->id, true);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, WGLUtils::identifier(ctx->id->id.back()), SymbolType::BiomeParam, ctx);
	sym->valueType = WGA_Value::typesByName.at(WGLUtils::identifier(ctx->type));
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
		throw WGLError(std::format("Variables are not allowed inside '{}'.", WGLUtils::getSymbolTypeName(effectiveTarget->symbolType())), ctx);

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, WGLUtils::identifier(ctx->id->id.back()), symbolType, ctx);
	sym->isExport = ctx->exportFlag;
	sym->valueType = WGA_Value::typesByName.at(WGLUtils::identifier(ctx->type));
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

	WGLSymbol *sym = new WGLSymbol(ctx_, directTarget, {}, SymbolType::Scope, ctx);
	currentScope_ += sym;
}

void WGLDeclarationPass::exitComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) {
	popScope(ctx);
}
