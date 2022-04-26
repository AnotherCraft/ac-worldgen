
// Generated from Woglac.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  WoglacParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, LineComment = 37, BlockComment = 38, 
    Whitespace = 39, Type = 40, BlockLiteral = 41, ComparisonOp = 42, BoolLiteral = 43, 
    StringLiteral = 44, MultOp = 45, Identifier = 46, NumericLiteral = 47
  };

  enum {
    RuleModule = 0, RuleStatement = 1, RuleScope = 2, RuleContentOrSemicolon = 3, 
    RulePragmaStatement = 4, RuleVariableDefinition = 5, RuleParamDefinition = 6, 
    RuleBiomeParamDefinition = 7, RuleParamSetStatement = 8, RuleBiomeConditionStatement = 9, 
    RuleStructureConditionStatement = 10, RuleRuleExpansionStatement = 11, 
    RuleComponentNodeStatement = 12, RuleComponentNodeStatementCommonPart = 13, 
    RuleComponentNodePropertiesSection = 14, RuleComponentNodeOrientationExpression = 15, 
    RuleComponentAreaStatement = 16, RuleComponentBlockStatement = 17, RuleComponentIncludeStatement = 18, 
    RuleComponentIncludeStatementParam = 19, RuleComponentIncludeStatementBlockParam = 20, 
    RuleComponentIncludeStatementNodeParam = 21, RulePositionExpression = 22, 
    RuleExpression = 23, RuleParentExpression = 24, RuleTernaryExpression = 25, 
    RuleLogicalExpression = 26, RuleAndExpression = 27, RuleOrExpression = 28, 
    RuleComparisonExpression = 29, RuleAddExpression = 30, RuleMultExpression = 31, 
    RuleUnaryExpression = 32, RuleInlineFunctionCallExpression = 33, RuleAtomicExpression = 34, 
    RuleArugmentListExpression = 35, RuleBiomeParamExpression = 36, RuleFunctionCallExpression = 37, 
    RuleExtendedIdentifier = 38, RuleLiteralExpression = 39
  };

  WoglacParser(antlr4::TokenStream *input);
  ~WoglacParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ModuleContext;
  class StatementContext;
  class ScopeContext;
  class ContentOrSemicolonContext;
  class PragmaStatementContext;
  class VariableDefinitionContext;
  class ParamDefinitionContext;
  class BiomeParamDefinitionContext;
  class ParamSetStatementContext;
  class BiomeConditionStatementContext;
  class StructureConditionStatementContext;
  class RuleExpansionStatementContext;
  class ComponentNodeStatementContext;
  class ComponentNodeStatementCommonPartContext;
  class ComponentNodePropertiesSectionContext;
  class ComponentNodeOrientationExpressionContext;
  class ComponentAreaStatementContext;
  class ComponentBlockStatementContext;
  class ComponentIncludeStatementContext;
  class ComponentIncludeStatementParamContext;
  class ComponentIncludeStatementBlockParamContext;
  class ComponentIncludeStatementNodeParamContext;
  class PositionExpressionContext;
  class ExpressionContext;
  class ParentExpressionContext;
  class TernaryExpressionContext;
  class LogicalExpressionContext;
  class AndExpressionContext;
  class OrExpressionContext;
  class ComparisonExpressionContext;
  class AddExpressionContext;
  class MultExpressionContext;
  class UnaryExpressionContext;
  class InlineFunctionCallExpressionContext;
  class AtomicExpressionContext;
  class ArugmentListExpressionContext;
  class BiomeParamExpressionContext;
  class FunctionCallExpressionContext;
  class ExtendedIdentifierContext;
  class LiteralExpressionContext; 

  class  ModuleContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::StatementContext *statementContext = nullptr;;
    std::vector<StatementContext *> content;;
    ModuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ModuleContext* module();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PragmaStatementContext *pragmaStatement();
    ParamDefinitionContext *paramDefinition();
    BiomeParamDefinitionContext *biomeParamDefinition();
    ParamSetStatementContext *paramSetStatement();
    BiomeConditionStatementContext *biomeConditionStatement();
    VariableDefinitionContext *variableDefinition();
    RuleExpansionStatementContext *ruleExpansionStatement();
    ScopeContext *scope();
    ComponentNodeStatementContext *componentNodeStatement();
    ComponentBlockStatementContext *componentBlockStatement();
    ComponentAreaStatementContext *componentAreaStatement();
    StructureConditionStatementContext *structureConditionStatement();
    ComponentIncludeStatementContext *componentIncludeStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  ScopeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *extend = nullptr;;
    antlr4::Token *type = nullptr;;
    WoglacParser::ExtendedIdentifierContext *id = nullptr;;
    WoglacParser::StatementContext *statementContext = nullptr;;
    std::vector<StatementContext *> content;;
    ScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContentOrSemicolonContext *contentOrSemicolon();
    ExtendedIdentifierContext *extendedIdentifier();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScopeContext* scope();

  class  ContentOrSemicolonContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::StatementContext *statementContext = nullptr;;
    std::vector<StatementContext *> content;;
    ContentOrSemicolonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContentOrSemicolonContext* contentOrSemicolon();

  class  PragmaStatementContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExtendedIdentifierContext *id = nullptr;;
    WoglacParser::LiteralExpressionContext *valLit = nullptr;;
    antlr4::Token *valId = nullptr;;
    PragmaStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExtendedIdentifierContext *extendedIdentifier();
    LiteralExpressionContext *literalExpression();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PragmaStatementContext* pragmaStatement();

  class  VariableDefinitionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *exportFlag = nullptr;;
    antlr4::Token *type = nullptr;;
    WoglacParser::ExtendedIdentifierContext *id = nullptr;;
    WoglacParser::ExpressionContext *val = nullptr;;
    VariableDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Type();
    ExtendedIdentifierContext *extendedIdentifier();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDefinitionContext* variableDefinition();

  class  ParamDefinitionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *targetType = nullptr;;
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *id = nullptr;;
    WoglacParser::ExpressionContext *defaultValue = nullptr;;
    ParamDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Type();
    antlr4::tree::TerminalNode *Identifier();
    ExpressionContext *expression();
    ExtendedIdentifierContext *extendedIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParamDefinitionContext* paramDefinition();

  class  BiomeParamDefinitionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *type = nullptr;;
    WoglacParser::ExtendedIdentifierContext *id = nullptr;;
    WoglacParser::ExpressionContext *defaultValue = nullptr;;
    BiomeParamDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Type();
    ExtendedIdentifierContext *extendedIdentifier();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BiomeParamDefinitionContext* biomeParamDefinition();

  class  ParamSetStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *targetType = nullptr;;
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    WoglacParser::ExtendedIdentifierContext *param = nullptr;;
    WoglacParser::ExpressionContext *value = nullptr;;
    ParamSetStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExtendedIdentifierContext *> extendedIdentifier();
    ExtendedIdentifierContext* extendedIdentifier(size_t i);
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParamSetStatementContext* paramSetStatement();

  class  BiomeConditionStatementContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    WoglacParser::ExtendedIdentifierContext *param = nullptr;;
    antlr4::Token *mean = nullptr;;
    antlr4::Token *dev = nullptr;;
    BiomeConditionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExtendedIdentifierContext *> extendedIdentifier();
    ExtendedIdentifierContext* extendedIdentifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NumericLiteral();
    antlr4::tree::TerminalNode* NumericLiteral(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BiomeConditionStatementContext* biomeConditionStatement();

  class  StructureConditionStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *targetType = nullptr;;
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    WoglacParser::ExpressionContext *cond = nullptr;;
    StructureConditionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    ExtendedIdentifierContext *extendedIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructureConditionStatementContext* structureConditionStatement();

  class  RuleExpansionStatementContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    WoglacParser::ExtendedIdentifierContext *expansionTarget = nullptr;;
    antlr4::Token *node = nullptr;;
    antlr4::Token *priority = nullptr;;
    antlr4::Token *probabilityRatio = nullptr;;
    WoglacParser::ContentOrSemicolonContext *content = nullptr;;
    RuleExpansionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContentOrSemicolonContext *contentOrSemicolon();
    std::vector<ExtendedIdentifierContext *> extendedIdentifier();
    ExtendedIdentifierContext* extendedIdentifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NumericLiteral();
    antlr4::tree::TerminalNode* NumericLiteral(size_t i);
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RuleExpansionStatementContext* ruleExpansionStatement();

  class  ComponentNodeStatementContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    WoglacParser::PositionExpressionContext *pos = nullptr;;
    WoglacParser::ComponentNodeStatementCommonPartContext *cmn = nullptr;;
    ComponentNodeStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PositionExpressionContext *positionExpression();
    ComponentNodeStatementCommonPartContext *componentNodeStatementCommonPart();
    ExtendedIdentifierContext *extendedIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentNodeStatementContext* componentNodeStatement();

  class  ComponentNodeStatementCommonPartContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ComponentNodePropertiesSectionContext *prop = nullptr;;
    antlr4::Token *group = nullptr;;
    WoglacParser::ExtendedIdentifierContext *rule_ = nullptr;;
    ComponentNodeStatementCommonPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContentOrSemicolonContext *contentOrSemicolon();
    ComponentNodePropertiesSectionContext *componentNodePropertiesSection();
    antlr4::tree::TerminalNode *Identifier();
    ExtendedIdentifierContext *extendedIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentNodeStatementCommonPartContext* componentNodeStatementCommonPart();

  class  ComponentNodePropertiesSectionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *notAdjacent = nullptr;;
    antlr4::Token *horizontalEdge = nullptr;;
    antlr4::Token *verticalEdge = nullptr;;
    WoglacParser::ComponentNodeOrientationExpressionContext *ori = nullptr;;
    WoglacParser::ComponentNodeOrientationExpressionContext *ori2 = nullptr;;
    ComponentNodePropertiesSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ComponentNodeOrientationExpressionContext *> componentNodeOrientationExpression();
    ComponentNodeOrientationExpressionContext* componentNodeOrientationExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentNodePropertiesSectionContext* componentNodePropertiesSection();

  class  ComponentNodeOrientationExpressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *dir = nullptr;;
    antlr4::Token *sign = nullptr;;
    ComponentNodeOrientationExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentNodeOrientationExpressionContext* componentNodeOrientationExpression();

  class  ComponentAreaStatementContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    WoglacParser::PositionExpressionContext *startPos = nullptr;;
    WoglacParser::PositionExpressionContext *endPos = nullptr;;
    antlr4::Token *canOverlap = nullptr;;
    antlr4::Token *mustOverlap = nullptr;;
    antlr4::Token *isVirtual = nullptr;;
    antlr4::Token *name = nullptr;;
    ComponentAreaStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PositionExpressionContext *> positionExpression();
    PositionExpressionContext* positionExpression(size_t i);
    ExtendedIdentifierContext *extendedIdentifier();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentAreaStatementContext* componentAreaStatement();

  class  ComponentBlockStatementContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExtendedIdentifierContext *target = nullptr;;
    WoglacParser::PositionExpressionContext *startPos = nullptr;;
    WoglacParser::PositionExpressionContext *endPos = nullptr;;
    WoglacParser::ExpressionContext *val = nullptr;;
    ComponentBlockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PositionExpressionContext *> positionExpression();
    PositionExpressionContext* positionExpression(size_t i);
    ExpressionContext *expression();
    ExtendedIdentifierContext *extendedIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentBlockStatementContext* componentBlockStatement();

  class  ComponentIncludeStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *file = nullptr;;
    WoglacParser::ComponentIncludeStatementParamContext *componentIncludeStatementParamContext = nullptr;;
    std::vector<ComponentIncludeStatementParamContext *> content;;
    ComponentIncludeStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();
    std::vector<ComponentIncludeStatementParamContext *> componentIncludeStatementParam();
    ComponentIncludeStatementParamContext* componentIncludeStatementParam(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentIncludeStatementContext* componentIncludeStatement();

  class  ComponentIncludeStatementParamContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ComponentIncludeStatementBlockParamContext *block = nullptr;;
    WoglacParser::ComponentIncludeStatementNodeParamContext *node = nullptr;;
    ComponentIncludeStatementParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ComponentIncludeStatementBlockParamContext *componentIncludeStatementBlockParam();
    ComponentIncludeStatementNodeParamContext *componentIncludeStatementNodeParam();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentIncludeStatementParamContext* componentIncludeStatementParam();

  class  ComponentIncludeStatementBlockParamContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;;
    WoglacParser::ExpressionContext *val = nullptr;;
    ComponentIncludeStatementBlockParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NumericLiteral();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentIncludeStatementBlockParamContext* componentIncludeStatementBlockParam();

  class  ComponentIncludeStatementNodeParamContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;;
    WoglacParser::ComponentNodeStatementCommonPartContext *com = nullptr;;
    ComponentIncludeStatementNodeParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NumericLiteral();
    ComponentNodeStatementCommonPartContext *componentNodeStatementCommonPart();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComponentIncludeStatementNodeParamContext* componentIncludeStatementNodeParam();

  class  PositionExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExpressionContext *x = nullptr;;
    WoglacParser::ExpressionContext *y = nullptr;;
    WoglacParser::ExpressionContext *z = nullptr;;
    WoglacParser::ExpressionContext *vec = nullptr;;
    PositionExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PositionExpressionContext* positionExpression();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::TernaryExpressionContext *e = nullptr;;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TernaryExpressionContext *ternaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class  ParentExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExpressionContext *e = nullptr;;
    ParentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParentExpressionContext* parentExpression();

  class  TernaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::LogicalExpressionContext *base = nullptr;;
    WoglacParser::LogicalExpressionContext *condition = nullptr;;
    WoglacParser::LogicalExpressionContext *thenBranch = nullptr;;
    WoglacParser::TernaryExpressionContext *elseBranch = nullptr;;
    TernaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicalExpressionContext *> logicalExpression();
    LogicalExpressionContext* logicalExpression(size_t i);
    TernaryExpressionContext *ternaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TernaryExpressionContext* ternaryExpression();

  class  LogicalExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::AndExpressionContext *a = nullptr;;
    WoglacParser::OrExpressionContext *o = nullptr;;
    LogicalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AndExpressionContext *andExpression();
    OrExpressionContext *orExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicalExpressionContext* logicalExpression();

  class  AndExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::AndExpressionContext *left = nullptr;;
    WoglacParser::ComparisonExpressionContext *base = nullptr;;
    WoglacParser::ComparisonExpressionContext *right = nullptr;;
    AndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ComparisonExpressionContext *comparisonExpression();
    AndExpressionContext *andExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AndExpressionContext* andExpression();
  AndExpressionContext* andExpression(int precedence);
  class  OrExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::OrExpressionContext *left = nullptr;;
    WoglacParser::ComparisonExpressionContext *base = nullptr;;
    WoglacParser::ComparisonExpressionContext *right = nullptr;;
    OrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ComparisonExpressionContext *comparisonExpression();
    OrExpressionContext *orExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OrExpressionContext* orExpression();
  OrExpressionContext* orExpression(int precedence);
  class  ComparisonExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::AddExpressionContext *base = nullptr;;
    WoglacParser::AddExpressionContext *left = nullptr;;
    antlr4::Token *op = nullptr;;
    WoglacParser::AddExpressionContext *right = nullptr;;
    ComparisonExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AddExpressionContext *> addExpression();
    AddExpressionContext* addExpression(size_t i);
    antlr4::tree::TerminalNode *ComparisonOp();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComparisonExpressionContext* comparisonExpression();

  class  AddExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::AddExpressionContext *left = nullptr;;
    WoglacParser::MultExpressionContext *base = nullptr;;
    antlr4::Token *op = nullptr;;
    WoglacParser::MultExpressionContext *right = nullptr;;
    AddExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MultExpressionContext *multExpression();
    AddExpressionContext *addExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AddExpressionContext* addExpression();
  AddExpressionContext* addExpression(int precedence);
  class  MultExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::MultExpressionContext *left = nullptr;;
    WoglacParser::UnaryExpressionContext *base = nullptr;;
    antlr4::Token *op = nullptr;;
    WoglacParser::UnaryExpressionContext *right = nullptr;;
    MultExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExpressionContext *unaryExpression();
    MultExpressionContext *multExpression();
    antlr4::tree::TerminalNode *MultOp();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MultExpressionContext* multExpression();
  MultExpressionContext* multExpression(int precedence);
  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::InlineFunctionCallExpressionContext *base = nullptr;;
    antlr4::Token *op = nullptr;;
    WoglacParser::InlineFunctionCallExpressionContext *arg = nullptr;;
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InlineFunctionCallExpressionContext *inlineFunctionCallExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  InlineFunctionCallExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::InlineFunctionCallExpressionContext *arg1 = nullptr;;
    WoglacParser::AtomicExpressionContext *base = nullptr;;
    antlr4::Token *id = nullptr;;
    WoglacParser::ArugmentListExpressionContext *args = nullptr;;
    InlineFunctionCallExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AtomicExpressionContext *atomicExpression();
    InlineFunctionCallExpressionContext *inlineFunctionCallExpression();
    antlr4::tree::TerminalNode *Identifier();
    ArugmentListExpressionContext *arugmentListExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InlineFunctionCallExpressionContext* inlineFunctionCallExpression();
  InlineFunctionCallExpressionContext* inlineFunctionCallExpression(int precedence);
  class  AtomicExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::FunctionCallExpressionContext *funcCall = nullptr;;
    WoglacParser::LiteralExpressionContext *lit = nullptr;;
    WoglacParser::ParentExpressionContext *par = nullptr;;
    WoglacParser::BiomeParamExpressionContext *bio = nullptr;;
    WoglacParser::ExtendedIdentifierContext *id = nullptr;;
    AtomicExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionCallExpressionContext *functionCallExpression();
    LiteralExpressionContext *literalExpression();
    ParentExpressionContext *parentExpression();
    BiomeParamExpressionContext *biomeParamExpression();
    ExtendedIdentifierContext *extendedIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtomicExpressionContext* atomicExpression();

  class  ArugmentListExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExpressionContext *expressionContext = nullptr;;
    std::vector<ExpressionContext *> args;;
    ArugmentListExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArugmentListExpressionContext* arugmentListExpression();

  class  BiomeParamExpressionContext : public antlr4::ParserRuleContext {
  public:
    WoglacParser::ExtendedIdentifierContext *param = nullptr;;
    antlr4::Token *method = nullptr;;
    WoglacParser::ExpressionContext *expressionContext = nullptr;;
    std::vector<ExpressionContext *> params;;
    BiomeParamExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExtendedIdentifierContext *extendedIdentifier();
    antlr4::tree::TerminalNode *Identifier();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BiomeParamExpressionContext* biomeParamExpression();

  class  FunctionCallExpressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;;
    WoglacParser::ArugmentListExpressionContext *args = nullptr;;
    FunctionCallExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    ArugmentListExpressionContext *arugmentListExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallExpressionContext* functionCallExpression();

  class  ExtendedIdentifierContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *identifierToken = nullptr;;
    std::vector<antlr4::Token *> id;;
    ExtendedIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExtendedIdentifierContext* extendedIdentifier();

  class  LiteralExpressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *num = nullptr;;
    antlr4::Token *block = nullptr;;
    antlr4::Token *bool_ = nullptr;;
    antlr4::Token *string = nullptr;;
    LiteralExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NumericLiteral();
    antlr4::tree::TerminalNode *BlockLiteral();
    antlr4::tree::TerminalNode *BoolLiteral();
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LiteralExpressionContext* literalExpression();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool andExpressionSempred(AndExpressionContext *_localctx, size_t predicateIndex);
  bool orExpressionSempred(OrExpressionContext *_localctx, size_t predicateIndex);
  bool addExpressionSempred(AddExpressionContext *_localctx, size_t predicateIndex);
  bool multExpressionSempred(MultExpressionContext *_localctx, size_t predicateIndex);
  bool inlineFunctionCallExpressionSempred(InlineFunctionCallExpressionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

