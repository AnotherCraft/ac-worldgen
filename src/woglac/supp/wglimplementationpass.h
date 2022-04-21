#pragma once

#include "wglinclude.h"

#include "worldgen/base/supp/wga_componentnode.h"
#include "worldgen/util/voxparser.h"

#include "wglpass.h"

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
	using ExpressionFunc = std::function<WGA_Value *(WGLAPIContext &ctx)>;
	using DependencyList = WGLContext::DependencyList;

	struct ExpressionResult {
		ExpressionFunc func;
		WGA_Value::ValueType type;
	};

private:
	ExpressionResult expression(WoglacParser::ExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::TernaryExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::LogicalExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::AndExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::OrExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::ComparisonExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::AddExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::MultExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::UnaryExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::AtomicExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::FunctionCallExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::LiteralExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::InlineFunctionCallExpressionContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::ExtendedIdentifierContext *ctx, DependencyList &deps);
	ExpressionResult expression(WoglacParser::BiomeParamExpressionContext *ctx, DependencyList &deps);

	ExpressionResult positionExpression(WoglacParser::PositionExpressionContext *ctx, DependencyList &deps);

private:
	void componentNodeCommonPart(WGLSymbol *sym, WoglacParser::ComponentNodeStatementCommonPartContext *ctx, WGLSymbol *component, DependencyList &deps, const std::function<void(WGLAPIContext &ctx, WGA_ComponentNode::Config &cfg)> &cfgFunc);

private:
	ExpressionResult functionCall(const std::string &functionName, const std::vector<ExpressionResult> &args, antlr4::ParserRuleContext *ctx);
	ExpressionResult binaryOperation(const std::string &op, const ExpressionResult &a, const ExpressionResult &b, antlr4::ParserRuleContext *ctx);

private:
	VOXParser voxParser_;
	std::vector<BlockWorldPos> componentIncludePositions_;

};

