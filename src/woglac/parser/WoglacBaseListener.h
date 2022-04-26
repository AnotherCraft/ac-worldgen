
// Generated from Woglac.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "WoglacListener.h"


/**
 * This class provides an empty implementation of WoglacListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  WoglacBaseListener : public WoglacListener {
public:

  virtual void enterModule(WoglacParser::ModuleContext * /*ctx*/) override { }
  virtual void exitModule(WoglacParser::ModuleContext * /*ctx*/) override { }

  virtual void enterStatement(WoglacParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(WoglacParser::StatementContext * /*ctx*/) override { }

  virtual void enterScope(WoglacParser::ScopeContext * /*ctx*/) override { }
  virtual void exitScope(WoglacParser::ScopeContext * /*ctx*/) override { }

  virtual void enterContentOrSemicolon(WoglacParser::ContentOrSemicolonContext * /*ctx*/) override { }
  virtual void exitContentOrSemicolon(WoglacParser::ContentOrSemicolonContext * /*ctx*/) override { }

  virtual void enterPragmaStatement(WoglacParser::PragmaStatementContext * /*ctx*/) override { }
  virtual void exitPragmaStatement(WoglacParser::PragmaStatementContext * /*ctx*/) override { }

  virtual void enterVariableDefinition(WoglacParser::VariableDefinitionContext * /*ctx*/) override { }
  virtual void exitVariableDefinition(WoglacParser::VariableDefinitionContext * /*ctx*/) override { }

  virtual void enterParamDefinition(WoglacParser::ParamDefinitionContext * /*ctx*/) override { }
  virtual void exitParamDefinition(WoglacParser::ParamDefinitionContext * /*ctx*/) override { }

  virtual void enterBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext * /*ctx*/) override { }
  virtual void exitBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext * /*ctx*/) override { }

  virtual void enterParamSetStatement(WoglacParser::ParamSetStatementContext * /*ctx*/) override { }
  virtual void exitParamSetStatement(WoglacParser::ParamSetStatementContext * /*ctx*/) override { }

  virtual void enterBiomeConditionStatement(WoglacParser::BiomeConditionStatementContext * /*ctx*/) override { }
  virtual void exitBiomeConditionStatement(WoglacParser::BiomeConditionStatementContext * /*ctx*/) override { }

  virtual void enterStructureConditionStatement(WoglacParser::StructureConditionStatementContext * /*ctx*/) override { }
  virtual void exitStructureConditionStatement(WoglacParser::StructureConditionStatementContext * /*ctx*/) override { }

  virtual void enterRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext * /*ctx*/) override { }
  virtual void exitRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext * /*ctx*/) override { }

  virtual void enterComponentNodeStatement(WoglacParser::ComponentNodeStatementContext * /*ctx*/) override { }
  virtual void exitComponentNodeStatement(WoglacParser::ComponentNodeStatementContext * /*ctx*/) override { }

  virtual void enterComponentNodeStatementCommonPart(WoglacParser::ComponentNodeStatementCommonPartContext * /*ctx*/) override { }
  virtual void exitComponentNodeStatementCommonPart(WoglacParser::ComponentNodeStatementCommonPartContext * /*ctx*/) override { }

  virtual void enterComponentNodePropertiesSection(WoglacParser::ComponentNodePropertiesSectionContext * /*ctx*/) override { }
  virtual void exitComponentNodePropertiesSection(WoglacParser::ComponentNodePropertiesSectionContext * /*ctx*/) override { }

  virtual void enterComponentNodeOrientationExpression(WoglacParser::ComponentNodeOrientationExpressionContext * /*ctx*/) override { }
  virtual void exitComponentNodeOrientationExpression(WoglacParser::ComponentNodeOrientationExpressionContext * /*ctx*/) override { }

  virtual void enterComponentAreaStatement(WoglacParser::ComponentAreaStatementContext * /*ctx*/) override { }
  virtual void exitComponentAreaStatement(WoglacParser::ComponentAreaStatementContext * /*ctx*/) override { }

  virtual void enterComponentBlockStatement(WoglacParser::ComponentBlockStatementContext * /*ctx*/) override { }
  virtual void exitComponentBlockStatement(WoglacParser::ComponentBlockStatementContext * /*ctx*/) override { }

  virtual void enterComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext * /*ctx*/) override { }
  virtual void exitComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext * /*ctx*/) override { }

  virtual void enterComponentIncludeStatementParam(WoglacParser::ComponentIncludeStatementParamContext * /*ctx*/) override { }
  virtual void exitComponentIncludeStatementParam(WoglacParser::ComponentIncludeStatementParamContext * /*ctx*/) override { }

  virtual void enterComponentIncludeStatementBlockParam(WoglacParser::ComponentIncludeStatementBlockParamContext * /*ctx*/) override { }
  virtual void exitComponentIncludeStatementBlockParam(WoglacParser::ComponentIncludeStatementBlockParamContext * /*ctx*/) override { }

  virtual void enterComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext * /*ctx*/) override { }
  virtual void exitComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext * /*ctx*/) override { }

  virtual void enterPositionExpression(WoglacParser::PositionExpressionContext * /*ctx*/) override { }
  virtual void exitPositionExpression(WoglacParser::PositionExpressionContext * /*ctx*/) override { }

  virtual void enterExpression(WoglacParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(WoglacParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterParentExpression(WoglacParser::ParentExpressionContext * /*ctx*/) override { }
  virtual void exitParentExpression(WoglacParser::ParentExpressionContext * /*ctx*/) override { }

  virtual void enterTernaryExpression(WoglacParser::TernaryExpressionContext * /*ctx*/) override { }
  virtual void exitTernaryExpression(WoglacParser::TernaryExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalExpression(WoglacParser::LogicalExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalExpression(WoglacParser::LogicalExpressionContext * /*ctx*/) override { }

  virtual void enterAndExpression(WoglacParser::AndExpressionContext * /*ctx*/) override { }
  virtual void exitAndExpression(WoglacParser::AndExpressionContext * /*ctx*/) override { }

  virtual void enterOrExpression(WoglacParser::OrExpressionContext * /*ctx*/) override { }
  virtual void exitOrExpression(WoglacParser::OrExpressionContext * /*ctx*/) override { }

  virtual void enterComparisonExpression(WoglacParser::ComparisonExpressionContext * /*ctx*/) override { }
  virtual void exitComparisonExpression(WoglacParser::ComparisonExpressionContext * /*ctx*/) override { }

  virtual void enterAddExpression(WoglacParser::AddExpressionContext * /*ctx*/) override { }
  virtual void exitAddExpression(WoglacParser::AddExpressionContext * /*ctx*/) override { }

  virtual void enterMultExpression(WoglacParser::MultExpressionContext * /*ctx*/) override { }
  virtual void exitMultExpression(WoglacParser::MultExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(WoglacParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(WoglacParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterInlineFunctionCallExpression(WoglacParser::InlineFunctionCallExpressionContext * /*ctx*/) override { }
  virtual void exitInlineFunctionCallExpression(WoglacParser::InlineFunctionCallExpressionContext * /*ctx*/) override { }

  virtual void enterAtomicExpression(WoglacParser::AtomicExpressionContext * /*ctx*/) override { }
  virtual void exitAtomicExpression(WoglacParser::AtomicExpressionContext * /*ctx*/) override { }

  virtual void enterArugmentListExpression(WoglacParser::ArugmentListExpressionContext * /*ctx*/) override { }
  virtual void exitArugmentListExpression(WoglacParser::ArugmentListExpressionContext * /*ctx*/) override { }

  virtual void enterBiomeParamExpression(WoglacParser::BiomeParamExpressionContext * /*ctx*/) override { }
  virtual void exitBiomeParamExpression(WoglacParser::BiomeParamExpressionContext * /*ctx*/) override { }

  virtual void enterFunctionCallExpression(WoglacParser::FunctionCallExpressionContext * /*ctx*/) override { }
  virtual void exitFunctionCallExpression(WoglacParser::FunctionCallExpressionContext * /*ctx*/) override { }

  virtual void enterExtendedIdentifier(WoglacParser::ExtendedIdentifierContext * /*ctx*/) override { }
  virtual void exitExtendedIdentifier(WoglacParser::ExtendedIdentifierContext * /*ctx*/) override { }

  virtual void enterLiteralExpression(WoglacParser::LiteralExpressionContext * /*ctx*/) override { }
  virtual void exitLiteralExpression(WoglacParser::LiteralExpressionContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

