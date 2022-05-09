#pragma once

#include "wglinclude.h"

#include "worldgen/base/supp/wga_componentnode.h"
#include "worldgen/util/voxparser.h"

#include "wglpass.h"
#include "wgldefines.h"

class WGLImplementationPass : public WGLPass {

protected:
	virtual void enterScope(WoglacParser::ScopeContext *ctx) override;
	virtual void exitScope(WoglacParser::ScopeContext *ctx) override;

	virtual void enterRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) override;
	virtual void exitRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) override;

	virtual void enterBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext *ctx) override;
	virtual void enterBiomeConditionStatement(WoglacParser::BiomeConditionStatementContext *ctx) override;
	virtual void enterVariableDefinition(WoglacParser::VariableDefinitionContext *ctx) override;
	virtual void enterParamDefinition(WoglacParser::ParamDefinitionContext *ctx) override;
	virtual void enterParamSetStatement(WoglacParser::ParamSetStatementContext *ctx) override;

	virtual void enterComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) override;
	virtual void exitComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) override;

	virtual void enterComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) override;
	virtual void exitComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) override;
	virtual void enterComponentIncludeStatementBlockParam(WoglacParser::ComponentIncludeStatementBlockParamContext *ctx) override;
	virtual void enterComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext *ctx) override;
	virtual void exitComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext *ctx) override;

	virtual void enterComponentAreaStatement(WoglacParser::ComponentAreaStatementContext *ctx) override;
	virtual void enterComponentBlockStatement(WoglacParser::ComponentBlockStatementContext *ctx) override;
	virtual void enterStructureConditionStatement(WoglacParser::StructureConditionStatementContext *ctx) override;
	virtual void enterPragmaStatement(WoglacParser::PragmaStatementContext *ctx) override;

private:
	WGLExpressionResult expression(WoglacParser::ExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::TernaryExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::LogicalExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::AndExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::OrExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::ComparisonExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::AddExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::MultExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::UnaryExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::AtomicExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::FunctionCallExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::LiteralExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::InlineFunctionCallExpressionContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::ExtendedIdentifierContext *ctx, WGLDependencyList &deps);
	WGLExpressionResult expression(WoglacParser::BiomeParamExpressionContext *ctx, WGLDependencyList &deps);

	WGLExpressionResult positionExpression(WoglacParser::PositionExpressionContext *ctx, WGLDependencyList &deps);

private:
	void componentNodeCommonPart(WGLSymbol *sym, WoglacParser::ComponentNodeStatementCommonPartContext *ctx, WGLSymbol *component, WGLDependencyList &deps, const std::function<void(WGLAPIContext &ctx, WGA_ComponentNode::Config &cfg)> &cfgFunc);

private:
	WGLExpressionResult functionCall(const std::string &functionName, const std::vector<WGLExpressionResult> &args, antlr4::ParserRuleContext *ctx);
	WGLExpressionResult binaryOperation(const std::string &op, const WGLExpressionResult &a, const WGLExpressionResult &b, antlr4::ParserRuleContext *ctx);

private:
	VOXParser voxParser_;
	std::string voxParserFileName_;
	std::vector<BlockWorldPos> componentIncludePositions_;

};

