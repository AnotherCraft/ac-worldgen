
// Generated from Woglac.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "WoglacParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by WoglacParser.
 */
class  WoglacListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterModule(WoglacParser::ModuleContext *ctx) = 0;
  virtual void exitModule(WoglacParser::ModuleContext *ctx) = 0;

  virtual void enterStatement(WoglacParser::StatementContext *ctx) = 0;
  virtual void exitStatement(WoglacParser::StatementContext *ctx) = 0;

  virtual void enterScope(WoglacParser::ScopeContext *ctx) = 0;
  virtual void exitScope(WoglacParser::ScopeContext *ctx) = 0;

  virtual void enterContentOrSemicolon(WoglacParser::ContentOrSemicolonContext *ctx) = 0;
  virtual void exitContentOrSemicolon(WoglacParser::ContentOrSemicolonContext *ctx) = 0;

  virtual void enterPragmaStatement(WoglacParser::PragmaStatementContext *ctx) = 0;
  virtual void exitPragmaStatement(WoglacParser::PragmaStatementContext *ctx) = 0;

  virtual void enterIncludeStatement(WoglacParser::IncludeStatementContext *ctx) = 0;
  virtual void exitIncludeStatement(WoglacParser::IncludeStatementContext *ctx) = 0;

  virtual void enterVariableDefinition(WoglacParser::VariableDefinitionContext *ctx) = 0;
  virtual void exitVariableDefinition(WoglacParser::VariableDefinitionContext *ctx) = 0;

  virtual void enterParamDefinition(WoglacParser::ParamDefinitionContext *ctx) = 0;
  virtual void exitParamDefinition(WoglacParser::ParamDefinitionContext *ctx) = 0;

  virtual void enterBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext *ctx) = 0;
  virtual void exitBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext *ctx) = 0;

  virtual void enterParamSetStatement(WoglacParser::ParamSetStatementContext *ctx) = 0;
  virtual void exitParamSetStatement(WoglacParser::ParamSetStatementContext *ctx) = 0;

  virtual void enterBiomeConditionStatement(WoglacParser::BiomeConditionStatementContext *ctx) = 0;
  virtual void exitBiomeConditionStatement(WoglacParser::BiomeConditionStatementContext *ctx) = 0;

  virtual void enterStructureConditionStatement(WoglacParser::StructureConditionStatementContext *ctx) = 0;
  virtual void exitStructureConditionStatement(WoglacParser::StructureConditionStatementContext *ctx) = 0;

  virtual void enterRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) = 0;
  virtual void exitRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) = 0;

  virtual void enterComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) = 0;
  virtual void exitComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) = 0;

  virtual void enterComponentNodeStatementCommonPart(WoglacParser::ComponentNodeStatementCommonPartContext *ctx) = 0;
  virtual void exitComponentNodeStatementCommonPart(WoglacParser::ComponentNodeStatementCommonPartContext *ctx) = 0;

  virtual void enterComponentNodePropertiesSection(WoglacParser::ComponentNodePropertiesSectionContext *ctx) = 0;
  virtual void exitComponentNodePropertiesSection(WoglacParser::ComponentNodePropertiesSectionContext *ctx) = 0;

  virtual void enterComponentNodeOrientationExpression(WoglacParser::ComponentNodeOrientationExpressionContext *ctx) = 0;
  virtual void exitComponentNodeOrientationExpression(WoglacParser::ComponentNodeOrientationExpressionContext *ctx) = 0;

  virtual void enterComponentAreaStatement(WoglacParser::ComponentAreaStatementContext *ctx) = 0;
  virtual void exitComponentAreaStatement(WoglacParser::ComponentAreaStatementContext *ctx) = 0;

  virtual void enterComponentBlockStatement(WoglacParser::ComponentBlockStatementContext *ctx) = 0;
  virtual void exitComponentBlockStatement(WoglacParser::ComponentBlockStatementContext *ctx) = 0;

  virtual void enterComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) = 0;
  virtual void exitComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) = 0;

  virtual void enterComponentIncludeStatementParam(WoglacParser::ComponentIncludeStatementParamContext *ctx) = 0;
  virtual void exitComponentIncludeStatementParam(WoglacParser::ComponentIncludeStatementParamContext *ctx) = 0;

  virtual void enterComponentIncludeStatementBlockParam(WoglacParser::ComponentIncludeStatementBlockParamContext *ctx) = 0;
  virtual void exitComponentIncludeStatementBlockParam(WoglacParser::ComponentIncludeStatementBlockParamContext *ctx) = 0;

  virtual void enterComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext *ctx) = 0;
  virtual void exitComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext *ctx) = 0;

  virtual void enterPositionExpression(WoglacParser::PositionExpressionContext *ctx) = 0;
  virtual void exitPositionExpression(WoglacParser::PositionExpressionContext *ctx) = 0;

  virtual void enterExpression(WoglacParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(WoglacParser::ExpressionContext *ctx) = 0;

  virtual void enterParentExpression(WoglacParser::ParentExpressionContext *ctx) = 0;
  virtual void exitParentExpression(WoglacParser::ParentExpressionContext *ctx) = 0;

  virtual void enterTernaryExpression(WoglacParser::TernaryExpressionContext *ctx) = 0;
  virtual void exitTernaryExpression(WoglacParser::TernaryExpressionContext *ctx) = 0;

  virtual void enterLogicalExpression(WoglacParser::LogicalExpressionContext *ctx) = 0;
  virtual void exitLogicalExpression(WoglacParser::LogicalExpressionContext *ctx) = 0;

  virtual void enterAndExpression(WoglacParser::AndExpressionContext *ctx) = 0;
  virtual void exitAndExpression(WoglacParser::AndExpressionContext *ctx) = 0;

  virtual void enterOrExpression(WoglacParser::OrExpressionContext *ctx) = 0;
  virtual void exitOrExpression(WoglacParser::OrExpressionContext *ctx) = 0;

  virtual void enterComparisonExpression(WoglacParser::ComparisonExpressionContext *ctx) = 0;
  virtual void exitComparisonExpression(WoglacParser::ComparisonExpressionContext *ctx) = 0;

  virtual void enterAddExpression(WoglacParser::AddExpressionContext *ctx) = 0;
  virtual void exitAddExpression(WoglacParser::AddExpressionContext *ctx) = 0;

  virtual void enterMultExpression(WoglacParser::MultExpressionContext *ctx) = 0;
  virtual void exitMultExpression(WoglacParser::MultExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(WoglacParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(WoglacParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterInlineFunctionCallExpression(WoglacParser::InlineFunctionCallExpressionContext *ctx) = 0;
  virtual void exitInlineFunctionCallExpression(WoglacParser::InlineFunctionCallExpressionContext *ctx) = 0;

  virtual void enterAtomicExpression(WoglacParser::AtomicExpressionContext *ctx) = 0;
  virtual void exitAtomicExpression(WoglacParser::AtomicExpressionContext *ctx) = 0;

  virtual void enterArugmentListExpression(WoglacParser::ArugmentListExpressionContext *ctx) = 0;
  virtual void exitArugmentListExpression(WoglacParser::ArugmentListExpressionContext *ctx) = 0;

  virtual void enterBiomeParamExpression(WoglacParser::BiomeParamExpressionContext *ctx) = 0;
  virtual void exitBiomeParamExpression(WoglacParser::BiomeParamExpressionContext *ctx) = 0;

  virtual void enterFunctionCallExpression(WoglacParser::FunctionCallExpressionContext *ctx) = 0;
  virtual void exitFunctionCallExpression(WoglacParser::FunctionCallExpressionContext *ctx) = 0;

  virtual void enterExtendedIdentifier(WoglacParser::ExtendedIdentifierContext *ctx) = 0;
  virtual void exitExtendedIdentifier(WoglacParser::ExtendedIdentifierContext *ctx) = 0;

  virtual void enterLiteralExpression(WoglacParser::LiteralExpressionContext *ctx) = 0;
  virtual void exitLiteralExpression(WoglacParser::LiteralExpressionContext *ctx) = 0;


};

