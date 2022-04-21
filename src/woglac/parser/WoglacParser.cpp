
// Generated from Woglac.g4 by ANTLR 4.7.2


#include "WoglacListener.h"

#include "WoglacParser.h"


using namespace antlrcpp;
using namespace antlr4;

WoglacParser::WoglacParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

WoglacParser::~WoglacParser() {
  delete _interpreter;
}

std::string WoglacParser::getGrammarFileName() const {
  return "Woglac.g4";
}

const std::vector<std::string>& WoglacParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& WoglacParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ModuleContext ------------------------------------------------------------------

WoglacParser::ModuleContext::ModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ModuleContext::EOF() {
  return getToken(WoglacParser::EOF, 0);
}

std::vector<WoglacParser::StatementContext *> WoglacParser::ModuleContext::statement() {
  return getRuleContexts<WoglacParser::StatementContext>();
}

WoglacParser::StatementContext* WoglacParser::ModuleContext::statement(size_t i) {
  return getRuleContext<WoglacParser::StatementContext>(i);
}


size_t WoglacParser::ModuleContext::getRuleIndex() const {
  return WoglacParser::RuleModule;
}

void WoglacParser::ModuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModule(this);
}

void WoglacParser::ModuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModule(this);
}

WoglacParser::ModuleContext* WoglacParser::module() {
  ModuleContext *_localctx = _tracker.createInstance<ModuleContext>(_ctx, getState());
  enterRule(_localctx, 0, WoglacParser::RuleModule);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WoglacParser::T__0)
      | (1ULL << WoglacParser::T__1)
      | (1ULL << WoglacParser::T__2)
      | (1ULL << WoglacParser::T__3)
      | (1ULL << WoglacParser::T__4)
      | (1ULL << WoglacParser::T__5)
      | (1ULL << WoglacParser::T__8)
      | (1ULL << WoglacParser::T__10)
      | (1ULL << WoglacParser::T__11)
      | (1ULL << WoglacParser::T__13)
      | (1ULL << WoglacParser::T__20)
      | (1ULL << WoglacParser::T__26)
      | (1ULL << WoglacParser::T__29)
      | (1ULL << WoglacParser::Type))) != 0)) {
      setState(80);
      dynamic_cast<ModuleContext *>(_localctx)->statementContext = statement();
      dynamic_cast<ModuleContext *>(_localctx)->content.push_back(dynamic_cast<ModuleContext *>(_localctx)->statementContext);
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(86);
    match(WoglacParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

WoglacParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::PragmaStatementContext* WoglacParser::StatementContext::pragmaStatement() {
  return getRuleContext<WoglacParser::PragmaStatementContext>(0);
}

WoglacParser::ParamDefinitionContext* WoglacParser::StatementContext::paramDefinition() {
  return getRuleContext<WoglacParser::ParamDefinitionContext>(0);
}

WoglacParser::BiomeParamDefinitionContext* WoglacParser::StatementContext::biomeParamDefinition() {
  return getRuleContext<WoglacParser::BiomeParamDefinitionContext>(0);
}

WoglacParser::ParamSetStatementContext* WoglacParser::StatementContext::paramSetStatement() {
  return getRuleContext<WoglacParser::ParamSetStatementContext>(0);
}

WoglacParser::BiomeConditionStatementContext* WoglacParser::StatementContext::biomeConditionStatement() {
  return getRuleContext<WoglacParser::BiomeConditionStatementContext>(0);
}

WoglacParser::VariableDefinitionContext* WoglacParser::StatementContext::variableDefinition() {
  return getRuleContext<WoglacParser::VariableDefinitionContext>(0);
}

WoglacParser::RuleExpansionStatementContext* WoglacParser::StatementContext::ruleExpansionStatement() {
  return getRuleContext<WoglacParser::RuleExpansionStatementContext>(0);
}

WoglacParser::ScopeContext* WoglacParser::StatementContext::scope() {
  return getRuleContext<WoglacParser::ScopeContext>(0);
}

WoglacParser::ComponentNodeStatementContext* WoglacParser::StatementContext::componentNodeStatement() {
  return getRuleContext<WoglacParser::ComponentNodeStatementContext>(0);
}

WoglacParser::ComponentBlockStatementContext* WoglacParser::StatementContext::componentBlockStatement() {
  return getRuleContext<WoglacParser::ComponentBlockStatementContext>(0);
}

WoglacParser::ComponentAreaStatementContext* WoglacParser::StatementContext::componentAreaStatement() {
  return getRuleContext<WoglacParser::ComponentAreaStatementContext>(0);
}

WoglacParser::StructureConditionStatementContext* WoglacParser::StatementContext::structureConditionStatement() {
  return getRuleContext<WoglacParser::StructureConditionStatementContext>(0);
}

WoglacParser::ComponentIncludeStatementContext* WoglacParser::StatementContext::componentIncludeStatement() {
  return getRuleContext<WoglacParser::ComponentIncludeStatementContext>(0);
}


size_t WoglacParser::StatementContext::getRuleIndex() const {
  return WoglacParser::RuleStatement;
}

void WoglacParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void WoglacParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

WoglacParser::StatementContext* WoglacParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, WoglacParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(101);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(88);
      pragmaStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(89);
      paramDefinition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(90);
      biomeParamDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(91);
      paramSetStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(92);
      biomeConditionStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(93);
      variableDefinition();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(94);
      ruleExpansionStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(95);
      scope();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(96);
      componentNodeStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(97);
      componentBlockStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(98);
      componentAreaStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(99);
      structureConditionStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(100);
      componentIncludeStatement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopeContext ------------------------------------------------------------------

WoglacParser::ScopeContext::ScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::ScopeContext::contentOrSemicolon() {
  return getRuleContext<WoglacParser::ContentOrSemicolonContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ScopeContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

std::vector<WoglacParser::StatementContext *> WoglacParser::ScopeContext::statement() {
  return getRuleContexts<WoglacParser::StatementContext>();
}

WoglacParser::StatementContext* WoglacParser::ScopeContext::statement(size_t i) {
  return getRuleContext<WoglacParser::StatementContext>(i);
}


size_t WoglacParser::ScopeContext::getRuleIndex() const {
  return WoglacParser::RuleScope;
}

void WoglacParser::ScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScope(this);
}

void WoglacParser::ScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScope(this);
}

WoglacParser::ScopeContext* WoglacParser::scope() {
  ScopeContext *_localctx = _tracker.createInstance<ScopeContext>(_ctx, getState());
  enterRule(_localctx, 4, WoglacParser::RuleScope);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(118);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__0:
      case WoglacParser::T__1:
      case WoglacParser::T__2:
      case WoglacParser::T__3:
      case WoglacParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(104);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == WoglacParser::T__0) {
          setState(103);
          dynamic_cast<ScopeContext *>(_localctx)->extend = match(WoglacParser::T__0);
        }
        setState(106);
        dynamic_cast<ScopeContext *>(_localctx)->type = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << WoglacParser::T__1)
          | (1ULL << WoglacParser::T__2)
          | (1ULL << WoglacParser::T__3)
          | (1ULL << WoglacParser::T__4))) != 0))) {
          dynamic_cast<ScopeContext *>(_localctx)->type = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(107);
        dynamic_cast<ScopeContext *>(_localctx)->id = extendedIdentifier();
        setState(108);
        contentOrSemicolon();
        break;
      }

      case WoglacParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(110);
        match(WoglacParser::T__5);
        setState(114);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << WoglacParser::T__0)
          | (1ULL << WoglacParser::T__1)
          | (1ULL << WoglacParser::T__2)
          | (1ULL << WoglacParser::T__3)
          | (1ULL << WoglacParser::T__4)
          | (1ULL << WoglacParser::T__5)
          | (1ULL << WoglacParser::T__8)
          | (1ULL << WoglacParser::T__10)
          | (1ULL << WoglacParser::T__11)
          | (1ULL << WoglacParser::T__13)
          | (1ULL << WoglacParser::T__20)
          | (1ULL << WoglacParser::T__26)
          | (1ULL << WoglacParser::T__29)
          | (1ULL << WoglacParser::Type))) != 0)) {
          setState(111);
          dynamic_cast<ScopeContext *>(_localctx)->statementContext = statement();
          dynamic_cast<ScopeContext *>(_localctx)->content.push_back(dynamic_cast<ScopeContext *>(_localctx)->statementContext);
          setState(116);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(117);
        match(WoglacParser::T__6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContentOrSemicolonContext ------------------------------------------------------------------

WoglacParser::ContentOrSemicolonContext::ContentOrSemicolonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::StatementContext *> WoglacParser::ContentOrSemicolonContext::statement() {
  return getRuleContexts<WoglacParser::StatementContext>();
}

WoglacParser::StatementContext* WoglacParser::ContentOrSemicolonContext::statement(size_t i) {
  return getRuleContext<WoglacParser::StatementContext>(i);
}


size_t WoglacParser::ContentOrSemicolonContext::getRuleIndex() const {
  return WoglacParser::RuleContentOrSemicolon;
}

void WoglacParser::ContentOrSemicolonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContentOrSemicolon(this);
}

void WoglacParser::ContentOrSemicolonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContentOrSemicolon(this);
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::contentOrSemicolon() {
  ContentOrSemicolonContext *_localctx = _tracker.createInstance<ContentOrSemicolonContext>(_ctx, getState());
  enterRule(_localctx, 6, WoglacParser::RuleContentOrSemicolon);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(129);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__5: {
        enterOuterAlt(_localctx, 1);
        setState(120);
        match(WoglacParser::T__5);
        setState(124);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << WoglacParser::T__0)
          | (1ULL << WoglacParser::T__1)
          | (1ULL << WoglacParser::T__2)
          | (1ULL << WoglacParser::T__3)
          | (1ULL << WoglacParser::T__4)
          | (1ULL << WoglacParser::T__5)
          | (1ULL << WoglacParser::T__8)
          | (1ULL << WoglacParser::T__10)
          | (1ULL << WoglacParser::T__11)
          | (1ULL << WoglacParser::T__13)
          | (1ULL << WoglacParser::T__20)
          | (1ULL << WoglacParser::T__26)
          | (1ULL << WoglacParser::T__29)
          | (1ULL << WoglacParser::Type))) != 0)) {
          setState(121);
          dynamic_cast<ContentOrSemicolonContext *>(_localctx)->statementContext = statement();
          dynamic_cast<ContentOrSemicolonContext *>(_localctx)->content.push_back(dynamic_cast<ContentOrSemicolonContext *>(_localctx)->statementContext);
          setState(126);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(127);
        match(WoglacParser::T__6);
        break;
      }

      case WoglacParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(128);
        match(WoglacParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PragmaStatementContext ------------------------------------------------------------------

WoglacParser::PragmaStatementContext::PragmaStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::PragmaStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

WoglacParser::LiteralExpressionContext* WoglacParser::PragmaStatementContext::literalExpression() {
  return getRuleContext<WoglacParser::LiteralExpressionContext>(0);
}

tree::TerminalNode* WoglacParser::PragmaStatementContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}


size_t WoglacParser::PragmaStatementContext::getRuleIndex() const {
  return WoglacParser::RulePragmaStatement;
}

void WoglacParser::PragmaStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPragmaStatement(this);
}

void WoglacParser::PragmaStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPragmaStatement(this);
}

WoglacParser::PragmaStatementContext* WoglacParser::pragmaStatement() {
  PragmaStatementContext *_localctx = _tracker.createInstance<PragmaStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, WoglacParser::RulePragmaStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    match(WoglacParser::T__8);
    setState(132);
    dynamic_cast<PragmaStatementContext *>(_localctx)->id = extendedIdentifier();
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__9) {
      setState(133);
      match(WoglacParser::T__9);
      setState(136);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case WoglacParser::T__27:
        case WoglacParser::T__35:
        case WoglacParser::BlockLiteral:
        case WoglacParser::BoolLiteral:
        case WoglacParser::StringLiteral:
        case WoglacParser::NumericLiteral: {
          setState(134);
          dynamic_cast<PragmaStatementContext *>(_localctx)->valLit = literalExpression();
          break;
        }

        case WoglacParser::Identifier: {
          setState(135);
          dynamic_cast<PragmaStatementContext *>(_localctx)->valId = match(WoglacParser::Identifier);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
    }
    setState(140);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDefinitionContext ------------------------------------------------------------------

WoglacParser::VariableDefinitionContext::VariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::VariableDefinitionContext::Type() {
  return getToken(WoglacParser::Type, 0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::VariableDefinitionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

WoglacParser::ExpressionContext* WoglacParser::VariableDefinitionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::VariableDefinitionContext::getRuleIndex() const {
  return WoglacParser::RuleVariableDefinition;
}

void WoglacParser::VariableDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDefinition(this);
}

void WoglacParser::VariableDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDefinition(this);
}

WoglacParser::VariableDefinitionContext* WoglacParser::variableDefinition() {
  VariableDefinitionContext *_localctx = _tracker.createInstance<VariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 10, WoglacParser::RuleVariableDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__10) {
      setState(142);
      dynamic_cast<VariableDefinitionContext *>(_localctx)->exportFlag = match(WoglacParser::T__10);
    }
    setState(145);
    dynamic_cast<VariableDefinitionContext *>(_localctx)->type = match(WoglacParser::Type);
    setState(146);
    dynamic_cast<VariableDefinitionContext *>(_localctx)->id = extendedIdentifier();
    setState(147);
    match(WoglacParser::T__9);
    setState(148);
    dynamic_cast<VariableDefinitionContext *>(_localctx)->val = expression();
    setState(149);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamDefinitionContext ------------------------------------------------------------------

WoglacParser::ParamDefinitionContext::ParamDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ParamDefinitionContext::Type() {
  return getToken(WoglacParser::Type, 0);
}

tree::TerminalNode* WoglacParser::ParamDefinitionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ExpressionContext* WoglacParser::ParamDefinitionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ParamDefinitionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ParamDefinitionContext::getRuleIndex() const {
  return WoglacParser::RuleParamDefinition;
}

void WoglacParser::ParamDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParamDefinition(this);
}

void WoglacParser::ParamDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParamDefinition(this);
}

WoglacParser::ParamDefinitionContext* WoglacParser::paramDefinition() {
  ParamDefinitionContext *_localctx = _tracker.createInstance<ParamDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 12, WoglacParser::RuleParamDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__2

    || _la == WoglacParser::T__3) {
      setState(151);
      dynamic_cast<ParamDefinitionContext *>(_localctx)->targetType = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == WoglacParser::T__2

      || _la == WoglacParser::T__3)) {
        dynamic_cast<ParamDefinitionContext *>(_localctx)->targetType = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(153);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::Identifier) {
        setState(152);
        dynamic_cast<ParamDefinitionContext *>(_localctx)->target = extendedIdentifier();
      }
    }
    setState(157);
    match(WoglacParser::T__11);
    setState(158);
    dynamic_cast<ParamDefinitionContext *>(_localctx)->type = match(WoglacParser::Type);
    setState(159);
    dynamic_cast<ParamDefinitionContext *>(_localctx)->id = match(WoglacParser::Identifier);
    setState(162);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__12) {
      setState(160);
      match(WoglacParser::T__12);
      setState(161);
      dynamic_cast<ParamDefinitionContext *>(_localctx)->defaultValue = expression();
    }
    setState(164);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BiomeParamDefinitionContext ------------------------------------------------------------------

WoglacParser::BiomeParamDefinitionContext::BiomeParamDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::BiomeParamDefinitionContext::Type() {
  return getToken(WoglacParser::Type, 0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::BiomeParamDefinitionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

WoglacParser::ExpressionContext* WoglacParser::BiomeParamDefinitionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::BiomeParamDefinitionContext::getRuleIndex() const {
  return WoglacParser::RuleBiomeParamDefinition;
}

void WoglacParser::BiomeParamDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBiomeParamDefinition(this);
}

void WoglacParser::BiomeParamDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBiomeParamDefinition(this);
}

WoglacParser::BiomeParamDefinitionContext* WoglacParser::biomeParamDefinition() {
  BiomeParamDefinitionContext *_localctx = _tracker.createInstance<BiomeParamDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 14, WoglacParser::RuleBiomeParamDefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    match(WoglacParser::T__4);
    setState(167);
    match(WoglacParser::T__11);
    setState(168);
    dynamic_cast<BiomeParamDefinitionContext *>(_localctx)->type = match(WoglacParser::Type);
    setState(169);
    dynamic_cast<BiomeParamDefinitionContext *>(_localctx)->id = extendedIdentifier();
    setState(170);
    match(WoglacParser::T__12);
    setState(171);
    dynamic_cast<BiomeParamDefinitionContext *>(_localctx)->defaultValue = expression();
    setState(172);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamSetStatementContext ------------------------------------------------------------------

WoglacParser::ParamSetStatementContext::ParamSetStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExtendedIdentifierContext *> WoglacParser::ParamSetStatementContext::extendedIdentifier() {
  return getRuleContexts<WoglacParser::ExtendedIdentifierContext>();
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ParamSetStatementContext::extendedIdentifier(size_t i) {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(i);
}

WoglacParser::ExpressionContext* WoglacParser::ParamSetStatementContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::ParamSetStatementContext::getRuleIndex() const {
  return WoglacParser::RuleParamSetStatement;
}

void WoglacParser::ParamSetStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParamSetStatement(this);
}

void WoglacParser::ParamSetStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParamSetStatement(this);
}

WoglacParser::ParamSetStatementContext* WoglacParser::paramSetStatement() {
  ParamSetStatementContext *_localctx = _tracker.createInstance<ParamSetStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, WoglacParser::RuleParamSetStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WoglacParser::T__2)
      | (1ULL << WoglacParser::T__3)
      | (1ULL << WoglacParser::T__4))) != 0)) {
      setState(174);
      dynamic_cast<ParamSetStatementContext *>(_localctx)->targetType = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << WoglacParser::T__2)
        | (1ULL << WoglacParser::T__3)
        | (1ULL << WoglacParser::T__4))) != 0))) {
        dynamic_cast<ParamSetStatementContext *>(_localctx)->targetType = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(175);
      dynamic_cast<ParamSetStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(178);
    match(WoglacParser::T__11);
    setState(179);
    dynamic_cast<ParamSetStatementContext *>(_localctx)->param = extendedIdentifier();
    setState(180);
    match(WoglacParser::T__9);
    setState(181);
    dynamic_cast<ParamSetStatementContext *>(_localctx)->value = expression();
    setState(182);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BiomeConditionStatementContext ------------------------------------------------------------------

WoglacParser::BiomeConditionStatementContext::BiomeConditionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExtendedIdentifierContext *> WoglacParser::BiomeConditionStatementContext::extendedIdentifier() {
  return getRuleContexts<WoglacParser::ExtendedIdentifierContext>();
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::BiomeConditionStatementContext::extendedIdentifier(size_t i) {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(i);
}

std::vector<tree::TerminalNode *> WoglacParser::BiomeConditionStatementContext::NumericLiteral() {
  return getTokens(WoglacParser::NumericLiteral);
}

tree::TerminalNode* WoglacParser::BiomeConditionStatementContext::NumericLiteral(size_t i) {
  return getToken(WoglacParser::NumericLiteral, i);
}


size_t WoglacParser::BiomeConditionStatementContext::getRuleIndex() const {
  return WoglacParser::RuleBiomeConditionStatement;
}

void WoglacParser::BiomeConditionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBiomeConditionStatement(this);
}

void WoglacParser::BiomeConditionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBiomeConditionStatement(this);
}

WoglacParser::BiomeConditionStatementContext* WoglacParser::biomeConditionStatement() {
  BiomeConditionStatementContext *_localctx = _tracker.createInstance<BiomeConditionStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, WoglacParser::RuleBiomeConditionStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__4) {
      setState(184);
      match(WoglacParser::T__4);
      setState(186);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::Identifier) {
        setState(185);
        dynamic_cast<BiomeConditionStatementContext *>(_localctx)->target = extendedIdentifier();
      }
    }
    setState(190);
    match(WoglacParser::T__13);
    setState(191);
    dynamic_cast<BiomeConditionStatementContext *>(_localctx)->param = extendedIdentifier();
    setState(192);
    match(WoglacParser::T__9);
    setState(193);
    dynamic_cast<BiomeConditionStatementContext *>(_localctx)->mean = match(WoglacParser::NumericLiteral);
    setState(194);
    match(WoglacParser::T__14);
    setState(195);
    dynamic_cast<BiomeConditionStatementContext *>(_localctx)->dev = match(WoglacParser::NumericLiteral);
    setState(196);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructureConditionStatementContext ------------------------------------------------------------------

WoglacParser::StructureConditionStatementContext::StructureConditionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExpressionContext* WoglacParser::StructureConditionStatementContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::StructureConditionStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::StructureConditionStatementContext::getRuleIndex() const {
  return WoglacParser::RuleStructureConditionStatement;
}

void WoglacParser::StructureConditionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructureConditionStatement(this);
}

void WoglacParser::StructureConditionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructureConditionStatement(this);
}

WoglacParser::StructureConditionStatementContext* WoglacParser::structureConditionStatement() {
  StructureConditionStatementContext *_localctx = _tracker.createInstance<StructureConditionStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, WoglacParser::RuleStructureConditionStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(202);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__2

    || _la == WoglacParser::T__3) {
      setState(198);
      dynamic_cast<StructureConditionStatementContext *>(_localctx)->targetType = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == WoglacParser::T__2

      || _la == WoglacParser::T__3)) {
        dynamic_cast<StructureConditionStatementContext *>(_localctx)->targetType = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(200);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::Identifier) {
        setState(199);
        dynamic_cast<StructureConditionStatementContext *>(_localctx)->target = extendedIdentifier();
      }
    }
    setState(204);
    match(WoglacParser::T__13);
    setState(205);
    dynamic_cast<StructureConditionStatementContext *>(_localctx)->cond = expression();
    setState(206);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleExpansionStatementContext ------------------------------------------------------------------

WoglacParser::RuleExpansionStatementContext::RuleExpansionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::RuleExpansionStatementContext::contentOrSemicolon() {
  return getRuleContext<WoglacParser::ContentOrSemicolonContext>(0);
}

std::vector<WoglacParser::ExtendedIdentifierContext *> WoglacParser::RuleExpansionStatementContext::extendedIdentifier() {
  return getRuleContexts<WoglacParser::ExtendedIdentifierContext>();
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::RuleExpansionStatementContext::extendedIdentifier(size_t i) {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(i);
}

tree::TerminalNode* WoglacParser::RuleExpansionStatementContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> WoglacParser::RuleExpansionStatementContext::NumericLiteral() {
  return getTokens(WoglacParser::NumericLiteral);
}

tree::TerminalNode* WoglacParser::RuleExpansionStatementContext::NumericLiteral(size_t i) {
  return getToken(WoglacParser::NumericLiteral, i);
}


size_t WoglacParser::RuleExpansionStatementContext::getRuleIndex() const {
  return WoglacParser::RuleRuleExpansionStatement;
}

void WoglacParser::RuleExpansionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleExpansionStatement(this);
}

void WoglacParser::RuleExpansionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleExpansionStatement(this);
}

WoglacParser::RuleExpansionStatementContext* WoglacParser::ruleExpansionStatement() {
  RuleExpansionStatementContext *_localctx = _tracker.createInstance<RuleExpansionStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, WoglacParser::RuleRuleExpansionStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(WoglacParser::T__2);
    setState(210);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(209);
      dynamic_cast<RuleExpansionStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(212);
    match(WoglacParser::T__15);
    setState(218);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::Identifier: {
        setState(213);
        dynamic_cast<RuleExpansionStatementContext *>(_localctx)->component = extendedIdentifier();
        setState(214);
        match(WoglacParser::T__16);
        setState(215);
        dynamic_cast<RuleExpansionStatementContext *>(_localctx)->node = match(WoglacParser::Identifier);
        break;
      }

      case WoglacParser::T__17: {
        setState(217);
        match(WoglacParser::T__17);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(222);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__18) {
      setState(220);
      match(WoglacParser::T__18);
      setState(221);
      dynamic_cast<RuleExpansionStatementContext *>(_localctx)->priority = match(WoglacParser::NumericLiteral);
    }
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__19) {
      setState(224);
      match(WoglacParser::T__19);
      setState(225);
      dynamic_cast<RuleExpansionStatementContext *>(_localctx)->probabilityRatio = match(WoglacParser::NumericLiteral);
    }
    setState(228);
    dynamic_cast<RuleExpansionStatementContext *>(_localctx)->content = contentOrSemicolon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodeStatementContext ------------------------------------------------------------------

WoglacParser::ComponentNodeStatementContext::ComponentNodeStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::PositionExpressionContext* WoglacParser::ComponentNodeStatementContext::positionExpression() {
  return getRuleContext<WoglacParser::PositionExpressionContext>(0);
}

WoglacParser::ComponentNodeStatementCommonPartContext* WoglacParser::ComponentNodeStatementContext::componentNodeStatementCommonPart() {
  return getRuleContext<WoglacParser::ComponentNodeStatementCommonPartContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentNodeStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ComponentNodeStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodeStatement;
}

void WoglacParser::ComponentNodeStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodeStatement(this);
}

void WoglacParser::ComponentNodeStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodeStatement(this);
}

WoglacParser::ComponentNodeStatementContext* WoglacParser::componentNodeStatement() {
  ComponentNodeStatementContext *_localctx = _tracker.createInstance<ComponentNodeStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, WoglacParser::RuleComponentNodeStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__3) {
      setState(230);
      match(WoglacParser::T__3);
      setState(231);
      dynamic_cast<ComponentNodeStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(234);
    match(WoglacParser::T__20);
    setState(235);
    dynamic_cast<ComponentNodeStatementContext *>(_localctx)->pos = positionExpression();
    setState(236);
    dynamic_cast<ComponentNodeStatementContext *>(_localctx)->cmn = componentNodeStatementCommonPart();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodeStatementCommonPartContext ------------------------------------------------------------------

WoglacParser::ComponentNodeStatementCommonPartContext::ComponentNodeStatementCommonPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::ComponentNodeStatementCommonPartContext::contentOrSemicolon() {
  return getRuleContext<WoglacParser::ContentOrSemicolonContext>(0);
}

WoglacParser::ComponentNodePropertiesSectionContext* WoglacParser::ComponentNodeStatementCommonPartContext::componentNodePropertiesSection() {
  return getRuleContext<WoglacParser::ComponentNodePropertiesSectionContext>(0);
}

tree::TerminalNode* WoglacParser::ComponentNodeStatementCommonPartContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentNodeStatementCommonPartContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ComponentNodeStatementCommonPartContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodeStatementCommonPart;
}

void WoglacParser::ComponentNodeStatementCommonPartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodeStatementCommonPart(this);
}

void WoglacParser::ComponentNodeStatementCommonPartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodeStatementCommonPart(this);
}

WoglacParser::ComponentNodeStatementCommonPartContext* WoglacParser::componentNodeStatementCommonPart() {
  ComponentNodeStatementCommonPartContext *_localctx = _tracker.createInstance<ComponentNodeStatementCommonPartContext>(_ctx, getState());
  enterRule(_localctx, 26, WoglacParser::RuleComponentNodeStatementCommonPart);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__21) {
      setState(238);
      dynamic_cast<ComponentNodeStatementCommonPartContext *>(_localctx)->prop = componentNodePropertiesSection();
    }
    setState(242);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(241);
      dynamic_cast<ComponentNodeStatementCommonPartContext *>(_localctx)->group = match(WoglacParser::Identifier);
    }
    setState(246);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__15) {
      setState(244);
      match(WoglacParser::T__15);
      setState(245);
      dynamic_cast<ComponentNodeStatementCommonPartContext *>(_localctx)->rule_ = extendedIdentifier();
    }
    setState(248);
    contentOrSemicolon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodePropertiesSectionContext ------------------------------------------------------------------

WoglacParser::ComponentNodePropertiesSectionContext::ComponentNodePropertiesSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ComponentNodeOrientationExpressionContext *> WoglacParser::ComponentNodePropertiesSectionContext::componentNodeOrientationExpression() {
  return getRuleContexts<WoglacParser::ComponentNodeOrientationExpressionContext>();
}

WoglacParser::ComponentNodeOrientationExpressionContext* WoglacParser::ComponentNodePropertiesSectionContext::componentNodeOrientationExpression(size_t i) {
  return getRuleContext<WoglacParser::ComponentNodeOrientationExpressionContext>(i);
}


size_t WoglacParser::ComponentNodePropertiesSectionContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodePropertiesSection;
}

void WoglacParser::ComponentNodePropertiesSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodePropertiesSection(this);
}

void WoglacParser::ComponentNodePropertiesSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodePropertiesSection(this);
}

WoglacParser::ComponentNodePropertiesSectionContext* WoglacParser::componentNodePropertiesSection() {
  ComponentNodePropertiesSectionContext *_localctx = _tracker.createInstance<ComponentNodePropertiesSectionContext>(_ctx, getState());
  enterRule(_localctx, 28, WoglacParser::RuleComponentNodePropertiesSection);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    match(WoglacParser::T__21);
    setState(252);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__9) {
      setState(251);
      dynamic_cast<ComponentNodePropertiesSectionContext *>(_localctx)->notAdjacent = match(WoglacParser::T__9);
    }
    setState(255);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__22) {
      setState(254);
      dynamic_cast<ComponentNodePropertiesSectionContext *>(_localctx)->horizontalEdge = match(WoglacParser::T__22);
    }
    setState(258);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__23) {
      setState(257);
      dynamic_cast<ComponentNodePropertiesSectionContext *>(_localctx)->verticalEdge = match(WoglacParser::T__23);
    }
    setState(260);
    dynamic_cast<ComponentNodePropertiesSectionContext *>(_localctx)->ori = componentNodeOrientationExpression();
    setState(262);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(261);
      dynamic_cast<ComponentNodePropertiesSectionContext *>(_localctx)->ori2 = componentNodeOrientationExpression();
    }
    setState(264);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodeOrientationExpressionContext ------------------------------------------------------------------

WoglacParser::ComponentNodeOrientationExpressionContext::ComponentNodeOrientationExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentNodeOrientationExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}


size_t WoglacParser::ComponentNodeOrientationExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodeOrientationExpression;
}

void WoglacParser::ComponentNodeOrientationExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodeOrientationExpression(this);
}

void WoglacParser::ComponentNodeOrientationExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodeOrientationExpression(this);
}

WoglacParser::ComponentNodeOrientationExpressionContext* WoglacParser::componentNodeOrientationExpression() {
  ComponentNodeOrientationExpressionContext *_localctx = _tracker.createInstance<ComponentNodeOrientationExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, WoglacParser::RuleComponentNodeOrientationExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    dynamic_cast<ComponentNodeOrientationExpressionContext *>(_localctx)->dir = match(WoglacParser::Identifier);
    setState(267);
    dynamic_cast<ComponentNodeOrientationExpressionContext *>(_localctx)->sign = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == WoglacParser::T__23

    || _la == WoglacParser::T__25)) {
      dynamic_cast<ComponentNodeOrientationExpressionContext *>(_localctx)->sign = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentAreaStatementContext ------------------------------------------------------------------

WoglacParser::ComponentAreaStatementContext::ComponentAreaStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::PositionExpressionContext *> WoglacParser::ComponentAreaStatementContext::positionExpression() {
  return getRuleContexts<WoglacParser::PositionExpressionContext>();
}

WoglacParser::PositionExpressionContext* WoglacParser::ComponentAreaStatementContext::positionExpression(size_t i) {
  return getRuleContext<WoglacParser::PositionExpressionContext>(i);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentAreaStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

tree::TerminalNode* WoglacParser::ComponentAreaStatementContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}


size_t WoglacParser::ComponentAreaStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentAreaStatement;
}

void WoglacParser::ComponentAreaStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentAreaStatement(this);
}

void WoglacParser::ComponentAreaStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentAreaStatement(this);
}

WoglacParser::ComponentAreaStatementContext* WoglacParser::componentAreaStatement() {
  ComponentAreaStatementContext *_localctx = _tracker.createInstance<ComponentAreaStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, WoglacParser::RuleComponentAreaStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(271);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__3) {
      setState(269);
      match(WoglacParser::T__3);
      setState(270);
      dynamic_cast<ComponentAreaStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(273);
    match(WoglacParser::T__26);
    setState(274);
    dynamic_cast<ComponentAreaStatementContext *>(_localctx)->startPos = positionExpression();
    setState(275);
    dynamic_cast<ComponentAreaStatementContext *>(_localctx)->endPos = positionExpression();
    setState(287);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__21) {
      setState(276);
      match(WoglacParser::T__21);
      setState(278);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__27) {
        setState(277);
        dynamic_cast<ComponentAreaStatementContext *>(_localctx)->canOverlap = match(WoglacParser::T__27);
      }
      setState(281);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__18) {
        setState(280);
        dynamic_cast<ComponentAreaStatementContext *>(_localctx)->mustOverlap = match(WoglacParser::T__18);
      }
      setState(284);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__28) {
        setState(283);
        dynamic_cast<ComponentAreaStatementContext *>(_localctx)->isVirtual = match(WoglacParser::T__28);
      }
      setState(286);
      match(WoglacParser::T__24);
    }
    setState(290);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(289);
      dynamic_cast<ComponentAreaStatementContext *>(_localctx)->name = match(WoglacParser::Identifier);
    }
    setState(292);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentBlockStatementContext ------------------------------------------------------------------

WoglacParser::ComponentBlockStatementContext::ComponentBlockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::PositionExpressionContext *> WoglacParser::ComponentBlockStatementContext::positionExpression() {
  return getRuleContexts<WoglacParser::PositionExpressionContext>();
}

WoglacParser::PositionExpressionContext* WoglacParser::ComponentBlockStatementContext::positionExpression(size_t i) {
  return getRuleContext<WoglacParser::PositionExpressionContext>(i);
}

WoglacParser::ExpressionContext* WoglacParser::ComponentBlockStatementContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentBlockStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ComponentBlockStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentBlockStatement;
}

void WoglacParser::ComponentBlockStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentBlockStatement(this);
}

void WoglacParser::ComponentBlockStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentBlockStatement(this);
}

WoglacParser::ComponentBlockStatementContext* WoglacParser::componentBlockStatement() {
  ComponentBlockStatementContext *_localctx = _tracker.createInstance<ComponentBlockStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, WoglacParser::RuleComponentBlockStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__3) {
      setState(294);
      match(WoglacParser::T__3);
      setState(295);
      dynamic_cast<ComponentBlockStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(298);
    match(WoglacParser::T__29);
    setState(299);
    dynamic_cast<ComponentBlockStatementContext *>(_localctx)->startPos = positionExpression();
    setState(301);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__21) {
      setState(300);
      dynamic_cast<ComponentBlockStatementContext *>(_localctx)->endPos = positionExpression();
    }
    setState(303);
    match(WoglacParser::T__9);
    setState(304);
    dynamic_cast<ComponentBlockStatementContext *>(_localctx)->val = expression();
    setState(305);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementContext::ComponentIncludeStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentIncludeStatementContext::StringLiteral() {
  return getToken(WoglacParser::StringLiteral, 0);
}

std::vector<WoglacParser::ComponentIncludeStatementParamContext *> WoglacParser::ComponentIncludeStatementContext::componentIncludeStatementParam() {
  return getRuleContexts<WoglacParser::ComponentIncludeStatementParamContext>();
}

WoglacParser::ComponentIncludeStatementParamContext* WoglacParser::ComponentIncludeStatementContext::componentIncludeStatementParam(size_t i) {
  return getRuleContext<WoglacParser::ComponentIncludeStatementParamContext>(i);
}


size_t WoglacParser::ComponentIncludeStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatement;
}

void WoglacParser::ComponentIncludeStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatement(this);
}

void WoglacParser::ComponentIncludeStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatement(this);
}

WoglacParser::ComponentIncludeStatementContext* WoglacParser::componentIncludeStatement() {
  ComponentIncludeStatementContext *_localctx = _tracker.createInstance<ComponentIncludeStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, WoglacParser::RuleComponentIncludeStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(307);
    match(WoglacParser::T__3);
    setState(308);
    match(WoglacParser::T__30);
    setState(309);
    dynamic_cast<ComponentIncludeStatementContext *>(_localctx)->file = match(WoglacParser::StringLiteral);
    setState(310);
    match(WoglacParser::T__5);
    setState(314);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WoglacParser::NumericLiteral) {
      setState(311);
      dynamic_cast<ComponentIncludeStatementContext *>(_localctx)->componentIncludeStatementParamContext = componentIncludeStatementParam();
      dynamic_cast<ComponentIncludeStatementContext *>(_localctx)->content.push_back(dynamic_cast<ComponentIncludeStatementContext *>(_localctx)->componentIncludeStatementParamContext);
      setState(316);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(317);
    match(WoglacParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementParamContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementParamContext::ComponentIncludeStatementParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ComponentIncludeStatementBlockParamContext* WoglacParser::ComponentIncludeStatementParamContext::componentIncludeStatementBlockParam() {
  return getRuleContext<WoglacParser::ComponentIncludeStatementBlockParamContext>(0);
}

WoglacParser::ComponentIncludeStatementNodeParamContext* WoglacParser::ComponentIncludeStatementParamContext::componentIncludeStatementNodeParam() {
  return getRuleContext<WoglacParser::ComponentIncludeStatementNodeParamContext>(0);
}


size_t WoglacParser::ComponentIncludeStatementParamContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatementParam;
}

void WoglacParser::ComponentIncludeStatementParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatementParam(this);
}

void WoglacParser::ComponentIncludeStatementParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatementParam(this);
}

WoglacParser::ComponentIncludeStatementParamContext* WoglacParser::componentIncludeStatementParam() {
  ComponentIncludeStatementParamContext *_localctx = _tracker.createInstance<ComponentIncludeStatementParamContext>(_ctx, getState());
  enterRule(_localctx, 38, WoglacParser::RuleComponentIncludeStatementParam);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(321);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(319);
      dynamic_cast<ComponentIncludeStatementParamContext *>(_localctx)->block = componentIncludeStatementBlockParam();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(320);
      dynamic_cast<ComponentIncludeStatementParamContext *>(_localctx)->node = componentIncludeStatementNodeParam();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementBlockParamContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementBlockParamContext::ComponentIncludeStatementBlockParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentIncludeStatementBlockParamContext::NumericLiteral() {
  return getToken(WoglacParser::NumericLiteral, 0);
}

WoglacParser::ExpressionContext* WoglacParser::ComponentIncludeStatementBlockParamContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::ComponentIncludeStatementBlockParamContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatementBlockParam;
}

void WoglacParser::ComponentIncludeStatementBlockParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatementBlockParam(this);
}

void WoglacParser::ComponentIncludeStatementBlockParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatementBlockParam(this);
}

WoglacParser::ComponentIncludeStatementBlockParamContext* WoglacParser::componentIncludeStatementBlockParam() {
  ComponentIncludeStatementBlockParamContext *_localctx = _tracker.createInstance<ComponentIncludeStatementBlockParamContext>(_ctx, getState());
  enterRule(_localctx, 40, WoglacParser::RuleComponentIncludeStatementBlockParam);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(323);
    dynamic_cast<ComponentIncludeStatementBlockParamContext *>(_localctx)->id = match(WoglacParser::NumericLiteral);
    setState(324);
    match(WoglacParser::T__15);
    setState(325);
    match(WoglacParser::T__29);
    setState(326);
    dynamic_cast<ComponentIncludeStatementBlockParamContext *>(_localctx)->val = expression();
    setState(327);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementNodeParamContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementNodeParamContext::ComponentIncludeStatementNodeParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentIncludeStatementNodeParamContext::NumericLiteral() {
  return getToken(WoglacParser::NumericLiteral, 0);
}

WoglacParser::ComponentNodeStatementCommonPartContext* WoglacParser::ComponentIncludeStatementNodeParamContext::componentNodeStatementCommonPart() {
  return getRuleContext<WoglacParser::ComponentNodeStatementCommonPartContext>(0);
}


size_t WoglacParser::ComponentIncludeStatementNodeParamContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatementNodeParam;
}

void WoglacParser::ComponentIncludeStatementNodeParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatementNodeParam(this);
}

void WoglacParser::ComponentIncludeStatementNodeParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatementNodeParam(this);
}

WoglacParser::ComponentIncludeStatementNodeParamContext* WoglacParser::componentIncludeStatementNodeParam() {
  ComponentIncludeStatementNodeParamContext *_localctx = _tracker.createInstance<ComponentIncludeStatementNodeParamContext>(_ctx, getState());
  enterRule(_localctx, 42, WoglacParser::RuleComponentIncludeStatementNodeParam);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    dynamic_cast<ComponentIncludeStatementNodeParamContext *>(_localctx)->id = match(WoglacParser::NumericLiteral);
    setState(330);
    match(WoglacParser::T__15);
    setState(331);
    match(WoglacParser::T__20);
    setState(332);
    dynamic_cast<ComponentIncludeStatementNodeParamContext *>(_localctx)->com = componentNodeStatementCommonPart();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PositionExpressionContext ------------------------------------------------------------------

WoglacParser::PositionExpressionContext::PositionExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExpressionContext *> WoglacParser::PositionExpressionContext::expression() {
  return getRuleContexts<WoglacParser::ExpressionContext>();
}

WoglacParser::ExpressionContext* WoglacParser::PositionExpressionContext::expression(size_t i) {
  return getRuleContext<WoglacParser::ExpressionContext>(i);
}


size_t WoglacParser::PositionExpressionContext::getRuleIndex() const {
  return WoglacParser::RulePositionExpression;
}

void WoglacParser::PositionExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPositionExpression(this);
}

void WoglacParser::PositionExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPositionExpression(this);
}

WoglacParser::PositionExpressionContext* WoglacParser::positionExpression() {
  PositionExpressionContext *_localctx = _tracker.createInstance<PositionExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, WoglacParser::RulePositionExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(334);
    match(WoglacParser::T__21);
    setState(342);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      setState(335);
      dynamic_cast<PositionExpressionContext *>(_localctx)->x = expression();
      setState(336);
      match(WoglacParser::T__31);
      setState(337);
      dynamic_cast<PositionExpressionContext *>(_localctx)->y = expression();
      setState(338);
      match(WoglacParser::T__31);
      setState(339);
      dynamic_cast<PositionExpressionContext *>(_localctx)->z = expression();
      break;
    }

    case 2: {
      setState(341);
      dynamic_cast<PositionExpressionContext *>(_localctx)->vec = expression();
      break;
    }

    }
    setState(344);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

WoglacParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::TernaryExpressionContext* WoglacParser::ExpressionContext::ternaryExpression() {
  return getRuleContext<WoglacParser::TernaryExpressionContext>(0);
}


size_t WoglacParser::ExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleExpression;
}

void WoglacParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void WoglacParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

WoglacParser::ExpressionContext* WoglacParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, WoglacParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(346);
    dynamic_cast<ExpressionContext *>(_localctx)->e = ternaryExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParentExpressionContext ------------------------------------------------------------------

WoglacParser::ParentExpressionContext::ParentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExpressionContext* WoglacParser::ParentExpressionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::ParentExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleParentExpression;
}

void WoglacParser::ParentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParentExpression(this);
}

void WoglacParser::ParentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParentExpression(this);
}

WoglacParser::ParentExpressionContext* WoglacParser::parentExpression() {
  ParentExpressionContext *_localctx = _tracker.createInstance<ParentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, WoglacParser::RuleParentExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(348);
    match(WoglacParser::T__21);
    setState(349);
    dynamic_cast<ParentExpressionContext *>(_localctx)->e = expression();
    setState(350);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TernaryExpressionContext ------------------------------------------------------------------

WoglacParser::TernaryExpressionContext::TernaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::LogicalExpressionContext *> WoglacParser::TernaryExpressionContext::logicalExpression() {
  return getRuleContexts<WoglacParser::LogicalExpressionContext>();
}

WoglacParser::LogicalExpressionContext* WoglacParser::TernaryExpressionContext::logicalExpression(size_t i) {
  return getRuleContext<WoglacParser::LogicalExpressionContext>(i);
}

WoglacParser::TernaryExpressionContext* WoglacParser::TernaryExpressionContext::ternaryExpression() {
  return getRuleContext<WoglacParser::TernaryExpressionContext>(0);
}


size_t WoglacParser::TernaryExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleTernaryExpression;
}

void WoglacParser::TernaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTernaryExpression(this);
}

void WoglacParser::TernaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTernaryExpression(this);
}

WoglacParser::TernaryExpressionContext* WoglacParser::ternaryExpression() {
  TernaryExpressionContext *_localctx = _tracker.createInstance<TernaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, WoglacParser::RuleTernaryExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(361);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(352);
      dynamic_cast<TernaryExpressionContext *>(_localctx)->base = logicalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(353);
      dynamic_cast<TernaryExpressionContext *>(_localctx)->condition = logicalExpression();
      setState(354);
      match(WoglacParser::T__28);
      setState(356);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << WoglacParser::T__4)
        | (1ULL << WoglacParser::T__18)
        | (1ULL << WoglacParser::T__21)
        | (1ULL << WoglacParser::T__23)
        | (1ULL << WoglacParser::T__25)
        | (1ULL << WoglacParser::T__27)
        | (1ULL << WoglacParser::T__35)
        | (1ULL << WoglacParser::BlockLiteral)
        | (1ULL << WoglacParser::BoolLiteral)
        | (1ULL << WoglacParser::StringLiteral)
        | (1ULL << WoglacParser::Identifier)
        | (1ULL << WoglacParser::NumericLiteral))) != 0)) {
        setState(355);
        dynamic_cast<TernaryExpressionContext *>(_localctx)->thenBranch = logicalExpression();
      }
      setState(358);
      match(WoglacParser::T__19);
      setState(359);
      dynamic_cast<TernaryExpressionContext *>(_localctx)->elseBranch = ternaryExpression();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalExpressionContext ------------------------------------------------------------------

WoglacParser::LogicalExpressionContext::LogicalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::AndExpressionContext* WoglacParser::LogicalExpressionContext::andExpression() {
  return getRuleContext<WoglacParser::AndExpressionContext>(0);
}

WoglacParser::OrExpressionContext* WoglacParser::LogicalExpressionContext::orExpression() {
  return getRuleContext<WoglacParser::OrExpressionContext>(0);
}


size_t WoglacParser::LogicalExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleLogicalExpression;
}

void WoglacParser::LogicalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalExpression(this);
}

void WoglacParser::LogicalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalExpression(this);
}

WoglacParser::LogicalExpressionContext* WoglacParser::logicalExpression() {
  LogicalExpressionContext *_localctx = _tracker.createInstance<LogicalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 52, WoglacParser::RuleLogicalExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(365);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(363);
      dynamic_cast<LogicalExpressionContext *>(_localctx)->a = andExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(364);
      dynamic_cast<LogicalExpressionContext *>(_localctx)->o = orExpression(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExpressionContext ------------------------------------------------------------------

WoglacParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ComparisonExpressionContext* WoglacParser::AndExpressionContext::comparisonExpression() {
  return getRuleContext<WoglacParser::ComparisonExpressionContext>(0);
}

WoglacParser::AndExpressionContext* WoglacParser::AndExpressionContext::andExpression() {
  return getRuleContext<WoglacParser::AndExpressionContext>(0);
}


size_t WoglacParser::AndExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleAndExpression;
}

void WoglacParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void WoglacParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}


WoglacParser::AndExpressionContext* WoglacParser::andExpression() {
   return andExpression(0);
}

WoglacParser::AndExpressionContext* WoglacParser::andExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, parentState);
  WoglacParser::AndExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, WoglacParser::RuleAndExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(368);
    dynamic_cast<AndExpressionContext *>(_localctx)->base = comparisonExpression();
    _ctx->stop = _input->LT(-1);
    setState(375);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AndExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleAndExpression);
        setState(370);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(371);
        match(WoglacParser::T__32);
        setState(372);
        dynamic_cast<AndExpressionContext *>(_localctx)->right = comparisonExpression(); 
      }
      setState(377);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- OrExpressionContext ------------------------------------------------------------------

WoglacParser::OrExpressionContext::OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ComparisonExpressionContext* WoglacParser::OrExpressionContext::comparisonExpression() {
  return getRuleContext<WoglacParser::ComparisonExpressionContext>(0);
}

WoglacParser::OrExpressionContext* WoglacParser::OrExpressionContext::orExpression() {
  return getRuleContext<WoglacParser::OrExpressionContext>(0);
}


size_t WoglacParser::OrExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleOrExpression;
}

void WoglacParser::OrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpression(this);
}

void WoglacParser::OrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpression(this);
}


WoglacParser::OrExpressionContext* WoglacParser::orExpression() {
   return orExpression(0);
}

WoglacParser::OrExpressionContext* WoglacParser::orExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::OrExpressionContext *_localctx = _tracker.createInstance<OrExpressionContext>(_ctx, parentState);
  WoglacParser::OrExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, WoglacParser::RuleOrExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(379);
    dynamic_cast<OrExpressionContext *>(_localctx)->base = comparisonExpression();
    _ctx->stop = _input->LT(-1);
    setState(386);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<OrExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleOrExpression);
        setState(381);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(382);
        match(WoglacParser::T__33);
        setState(383);
        dynamic_cast<OrExpressionContext *>(_localctx)->right = comparisonExpression(); 
      }
      setState(388);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ComparisonExpressionContext ------------------------------------------------------------------

WoglacParser::ComparisonExpressionContext::ComparisonExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::AddExpressionContext *> WoglacParser::ComparisonExpressionContext::addExpression() {
  return getRuleContexts<WoglacParser::AddExpressionContext>();
}

WoglacParser::AddExpressionContext* WoglacParser::ComparisonExpressionContext::addExpression(size_t i) {
  return getRuleContext<WoglacParser::AddExpressionContext>(i);
}

tree::TerminalNode* WoglacParser::ComparisonExpressionContext::ComparisonOp() {
  return getToken(WoglacParser::ComparisonOp, 0);
}


size_t WoglacParser::ComparisonExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleComparisonExpression;
}

void WoglacParser::ComparisonExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparisonExpression(this);
}

void WoglacParser::ComparisonExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparisonExpression(this);
}

WoglacParser::ComparisonExpressionContext* WoglacParser::comparisonExpression() {
  ComparisonExpressionContext *_localctx = _tracker.createInstance<ComparisonExpressionContext>(_ctx, getState());
  enterRule(_localctx, 58, WoglacParser::RuleComparisonExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(394);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(389);
      dynamic_cast<ComparisonExpressionContext *>(_localctx)->base = addExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(390);
      dynamic_cast<ComparisonExpressionContext *>(_localctx)->left = addExpression(0);
      setState(391);
      dynamic_cast<ComparisonExpressionContext *>(_localctx)->op = match(WoglacParser::ComparisonOp);
      setState(392);
      dynamic_cast<ComparisonExpressionContext *>(_localctx)->right = addExpression(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpressionContext ------------------------------------------------------------------

WoglacParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::MultExpressionContext* WoglacParser::AddExpressionContext::multExpression() {
  return getRuleContext<WoglacParser::MultExpressionContext>(0);
}

WoglacParser::AddExpressionContext* WoglacParser::AddExpressionContext::addExpression() {
  return getRuleContext<WoglacParser::AddExpressionContext>(0);
}


size_t WoglacParser::AddExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleAddExpression;
}

void WoglacParser::AddExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExpression(this);
}

void WoglacParser::AddExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExpression(this);
}


WoglacParser::AddExpressionContext* WoglacParser::addExpression() {
   return addExpression(0);
}

WoglacParser::AddExpressionContext* WoglacParser::addExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::AddExpressionContext *_localctx = _tracker.createInstance<AddExpressionContext>(_ctx, parentState);
  WoglacParser::AddExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, WoglacParser::RuleAddExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(397);
    dynamic_cast<AddExpressionContext *>(_localctx)->base = multExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(404);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleAddExpression);
        setState(399);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(400);
        dynamic_cast<AddExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == WoglacParser::T__23

        || _la == WoglacParser::T__25)) {
          dynamic_cast<AddExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(401);
        dynamic_cast<AddExpressionContext *>(_localctx)->right = multExpression(0); 
      }
      setState(406);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MultExpressionContext ------------------------------------------------------------------

WoglacParser::MultExpressionContext::MultExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::UnaryExpressionContext* WoglacParser::MultExpressionContext::unaryExpression() {
  return getRuleContext<WoglacParser::UnaryExpressionContext>(0);
}

WoglacParser::MultExpressionContext* WoglacParser::MultExpressionContext::multExpression() {
  return getRuleContext<WoglacParser::MultExpressionContext>(0);
}

tree::TerminalNode* WoglacParser::MultExpressionContext::MultOp() {
  return getToken(WoglacParser::MultOp, 0);
}


size_t WoglacParser::MultExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleMultExpression;
}

void WoglacParser::MultExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultExpression(this);
}

void WoglacParser::MultExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultExpression(this);
}


WoglacParser::MultExpressionContext* WoglacParser::multExpression() {
   return multExpression(0);
}

WoglacParser::MultExpressionContext* WoglacParser::multExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::MultExpressionContext *_localctx = _tracker.createInstance<MultExpressionContext>(_ctx, parentState);
  WoglacParser::MultExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, WoglacParser::RuleMultExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(408);
    dynamic_cast<MultExpressionContext *>(_localctx)->base = unaryExpression();
    _ctx->stop = _input->LT(-1);
    setState(415);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MultExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleMultExpression);
        setState(410);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(411);
        dynamic_cast<MultExpressionContext *>(_localctx)->op = match(WoglacParser::MultOp);
        setState(412);
        dynamic_cast<MultExpressionContext *>(_localctx)->right = unaryExpression(); 
      }
      setState(417);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

WoglacParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::UnaryExpressionContext::inlineFunctionCallExpression() {
  return getRuleContext<WoglacParser::InlineFunctionCallExpressionContext>(0);
}


size_t WoglacParser::UnaryExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleUnaryExpression;
}

void WoglacParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void WoglacParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}

WoglacParser::UnaryExpressionContext* WoglacParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 64, WoglacParser::RuleUnaryExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(423);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__4:
      case WoglacParser::T__21:
      case WoglacParser::T__27:
      case WoglacParser::T__35:
      case WoglacParser::BlockLiteral:
      case WoglacParser::BoolLiteral:
      case WoglacParser::StringLiteral:
      case WoglacParser::Identifier:
      case WoglacParser::NumericLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(418);
        dynamic_cast<UnaryExpressionContext *>(_localctx)->base = inlineFunctionCallExpression(0);
        break;
      }

      case WoglacParser::T__23:
      case WoglacParser::T__25: {
        enterOuterAlt(_localctx, 2);
        setState(419);
        dynamic_cast<UnaryExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == WoglacParser::T__23

        || _la == WoglacParser::T__25)) {
          dynamic_cast<UnaryExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(420);
        dynamic_cast<UnaryExpressionContext *>(_localctx)->arg = inlineFunctionCallExpression(0);
        break;
      }

      case WoglacParser::T__18: {
        enterOuterAlt(_localctx, 3);
        setState(421);
        dynamic_cast<UnaryExpressionContext *>(_localctx)->op = match(WoglacParser::T__18);
        setState(422);
        dynamic_cast<UnaryExpressionContext *>(_localctx)->arg = inlineFunctionCallExpression(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InlineFunctionCallExpressionContext ------------------------------------------------------------------

WoglacParser::InlineFunctionCallExpressionContext::InlineFunctionCallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::AtomicExpressionContext* WoglacParser::InlineFunctionCallExpressionContext::atomicExpression() {
  return getRuleContext<WoglacParser::AtomicExpressionContext>(0);
}

WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::InlineFunctionCallExpressionContext::inlineFunctionCallExpression() {
  return getRuleContext<WoglacParser::InlineFunctionCallExpressionContext>(0);
}

tree::TerminalNode* WoglacParser::InlineFunctionCallExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ArugmentListExpressionContext* WoglacParser::InlineFunctionCallExpressionContext::arugmentListExpression() {
  return getRuleContext<WoglacParser::ArugmentListExpressionContext>(0);
}


size_t WoglacParser::InlineFunctionCallExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleInlineFunctionCallExpression;
}

void WoglacParser::InlineFunctionCallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInlineFunctionCallExpression(this);
}

void WoglacParser::InlineFunctionCallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInlineFunctionCallExpression(this);
}


WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::inlineFunctionCallExpression() {
   return inlineFunctionCallExpression(0);
}

WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::inlineFunctionCallExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::InlineFunctionCallExpressionContext *_localctx = _tracker.createInstance<InlineFunctionCallExpressionContext>(_ctx, parentState);
  WoglacParser::InlineFunctionCallExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 66;
  enterRecursionRule(_localctx, 66, WoglacParser::RuleInlineFunctionCallExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(426);
    dynamic_cast<InlineFunctionCallExpressionContext *>(_localctx)->base = atomicExpression();
    _ctx->stop = _input->LT(-1);
    setState(434);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<InlineFunctionCallExpressionContext>(parentContext, parentState);
        _localctx->arg1 = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleInlineFunctionCallExpression);
        setState(428);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(429);
        match(WoglacParser::T__16);
        setState(430);
        dynamic_cast<InlineFunctionCallExpressionContext *>(_localctx)->id = match(WoglacParser::Identifier);
        setState(431);
        dynamic_cast<InlineFunctionCallExpressionContext *>(_localctx)->args = arugmentListExpression(); 
      }
      setState(436);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AtomicExpressionContext ------------------------------------------------------------------

WoglacParser::AtomicExpressionContext::AtomicExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::FunctionCallExpressionContext* WoglacParser::AtomicExpressionContext::functionCallExpression() {
  return getRuleContext<WoglacParser::FunctionCallExpressionContext>(0);
}

WoglacParser::LiteralExpressionContext* WoglacParser::AtomicExpressionContext::literalExpression() {
  return getRuleContext<WoglacParser::LiteralExpressionContext>(0);
}

WoglacParser::ParentExpressionContext* WoglacParser::AtomicExpressionContext::parentExpression() {
  return getRuleContext<WoglacParser::ParentExpressionContext>(0);
}

WoglacParser::BiomeParamExpressionContext* WoglacParser::AtomicExpressionContext::biomeParamExpression() {
  return getRuleContext<WoglacParser::BiomeParamExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::AtomicExpressionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::AtomicExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleAtomicExpression;
}

void WoglacParser::AtomicExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtomicExpression(this);
}

void WoglacParser::AtomicExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtomicExpression(this);
}

WoglacParser::AtomicExpressionContext* WoglacParser::atomicExpression() {
  AtomicExpressionContext *_localctx = _tracker.createInstance<AtomicExpressionContext>(_ctx, getState());
  enterRule(_localctx, 68, WoglacParser::RuleAtomicExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(442);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(437);
      dynamic_cast<AtomicExpressionContext *>(_localctx)->funcCall = functionCallExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(438);
      dynamic_cast<AtomicExpressionContext *>(_localctx)->lit = literalExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(439);
      dynamic_cast<AtomicExpressionContext *>(_localctx)->par = parentExpression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(440);
      dynamic_cast<AtomicExpressionContext *>(_localctx)->bio = biomeParamExpression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(441);
      dynamic_cast<AtomicExpressionContext *>(_localctx)->id = extendedIdentifier();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArugmentListExpressionContext ------------------------------------------------------------------

WoglacParser::ArugmentListExpressionContext::ArugmentListExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExpressionContext *> WoglacParser::ArugmentListExpressionContext::expression() {
  return getRuleContexts<WoglacParser::ExpressionContext>();
}

WoglacParser::ExpressionContext* WoglacParser::ArugmentListExpressionContext::expression(size_t i) {
  return getRuleContext<WoglacParser::ExpressionContext>(i);
}


size_t WoglacParser::ArugmentListExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleArugmentListExpression;
}

void WoglacParser::ArugmentListExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArugmentListExpression(this);
}

void WoglacParser::ArugmentListExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArugmentListExpression(this);
}

WoglacParser::ArugmentListExpressionContext* WoglacParser::arugmentListExpression() {
  ArugmentListExpressionContext *_localctx = _tracker.createInstance<ArugmentListExpressionContext>(_ctx, getState());
  enterRule(_localctx, 70, WoglacParser::RuleArugmentListExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(444);
    match(WoglacParser::T__21);
    setState(456);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WoglacParser::T__4)
      | (1ULL << WoglacParser::T__18)
      | (1ULL << WoglacParser::T__21)
      | (1ULL << WoglacParser::T__23)
      | (1ULL << WoglacParser::T__25)
      | (1ULL << WoglacParser::T__27)
      | (1ULL << WoglacParser::T__35)
      | (1ULL << WoglacParser::BlockLiteral)
      | (1ULL << WoglacParser::BoolLiteral)
      | (1ULL << WoglacParser::StringLiteral)
      | (1ULL << WoglacParser::Identifier)
      | (1ULL << WoglacParser::NumericLiteral))) != 0)) {
      setState(445);
      dynamic_cast<ArugmentListExpressionContext *>(_localctx)->expressionContext = expression();
      dynamic_cast<ArugmentListExpressionContext *>(_localctx)->args.push_back(dynamic_cast<ArugmentListExpressionContext *>(_localctx)->expressionContext);
      setState(450);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(446);
          match(WoglacParser::T__31);
          setState(447);
          dynamic_cast<ArugmentListExpressionContext *>(_localctx)->expressionContext = expression();
          dynamic_cast<ArugmentListExpressionContext *>(_localctx)->args.push_back(dynamic_cast<ArugmentListExpressionContext *>(_localctx)->expressionContext); 
        }
        setState(452);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
      }
      setState(454);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__31) {
        setState(453);
        match(WoglacParser::T__31);
      }
    }
    setState(458);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BiomeParamExpressionContext ------------------------------------------------------------------

WoglacParser::BiomeParamExpressionContext::BiomeParamExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::BiomeParamExpressionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

tree::TerminalNode* WoglacParser::BiomeParamExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

std::vector<WoglacParser::ExpressionContext *> WoglacParser::BiomeParamExpressionContext::expression() {
  return getRuleContexts<WoglacParser::ExpressionContext>();
}

WoglacParser::ExpressionContext* WoglacParser::BiomeParamExpressionContext::expression(size_t i) {
  return getRuleContext<WoglacParser::ExpressionContext>(i);
}


size_t WoglacParser::BiomeParamExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleBiomeParamExpression;
}

void WoglacParser::BiomeParamExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBiomeParamExpression(this);
}

void WoglacParser::BiomeParamExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBiomeParamExpression(this);
}

WoglacParser::BiomeParamExpressionContext* WoglacParser::biomeParamExpression() {
  BiomeParamExpressionContext *_localctx = _tracker.createInstance<BiomeParamExpressionContext>(_ctx, getState());
  enterRule(_localctx, 72, WoglacParser::RuleBiomeParamExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(460);
    match(WoglacParser::T__4);
    setState(461);
    match(WoglacParser::T__21);
    setState(462);
    dynamic_cast<BiomeParamExpressionContext *>(_localctx)->param = extendedIdentifier();
    setState(463);
    match(WoglacParser::T__31);
    setState(464);
    dynamic_cast<BiomeParamExpressionContext *>(_localctx)->method = match(WoglacParser::Identifier);
    setState(469);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WoglacParser::T__31) {
      setState(465);
      match(WoglacParser::T__31);
      setState(466);
      dynamic_cast<BiomeParamExpressionContext *>(_localctx)->expressionContext = expression();
      dynamic_cast<BiomeParamExpressionContext *>(_localctx)->params.push_back(dynamic_cast<BiomeParamExpressionContext *>(_localctx)->expressionContext);
      setState(471);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(472);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallExpressionContext ------------------------------------------------------------------

WoglacParser::FunctionCallExpressionContext::FunctionCallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::FunctionCallExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ArugmentListExpressionContext* WoglacParser::FunctionCallExpressionContext::arugmentListExpression() {
  return getRuleContext<WoglacParser::ArugmentListExpressionContext>(0);
}


size_t WoglacParser::FunctionCallExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleFunctionCallExpression;
}

void WoglacParser::FunctionCallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallExpression(this);
}

void WoglacParser::FunctionCallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallExpression(this);
}

WoglacParser::FunctionCallExpressionContext* WoglacParser::functionCallExpression() {
  FunctionCallExpressionContext *_localctx = _tracker.createInstance<FunctionCallExpressionContext>(_ctx, getState());
  enterRule(_localctx, 74, WoglacParser::RuleFunctionCallExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(474);
    dynamic_cast<FunctionCallExpressionContext *>(_localctx)->id = match(WoglacParser::Identifier);
    setState(475);
    dynamic_cast<FunctionCallExpressionContext *>(_localctx)->args = arugmentListExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExtendedIdentifierContext ------------------------------------------------------------------

WoglacParser::ExtendedIdentifierContext::ExtendedIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> WoglacParser::ExtendedIdentifierContext::Identifier() {
  return getTokens(WoglacParser::Identifier);
}

tree::TerminalNode* WoglacParser::ExtendedIdentifierContext::Identifier(size_t i) {
  return getToken(WoglacParser::Identifier, i);
}


size_t WoglacParser::ExtendedIdentifierContext::getRuleIndex() const {
  return WoglacParser::RuleExtendedIdentifier;
}

void WoglacParser::ExtendedIdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtendedIdentifier(this);
}

void WoglacParser::ExtendedIdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtendedIdentifier(this);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::extendedIdentifier() {
  ExtendedIdentifierContext *_localctx = _tracker.createInstance<ExtendedIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 76, WoglacParser::RuleExtendedIdentifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(477);
    dynamic_cast<ExtendedIdentifierContext *>(_localctx)->identifierToken = match(WoglacParser::Identifier);
    dynamic_cast<ExtendedIdentifierContext *>(_localctx)->id.push_back(dynamic_cast<ExtendedIdentifierContext *>(_localctx)->identifierToken);
    setState(482);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(478);
        match(WoglacParser::T__34);
        setState(479);
        dynamic_cast<ExtendedIdentifierContext *>(_localctx)->identifierToken = match(WoglacParser::Identifier);
        dynamic_cast<ExtendedIdentifierContext *>(_localctx)->id.push_back(dynamic_cast<ExtendedIdentifierContext *>(_localctx)->identifierToken); 
      }
      setState(484);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralExpressionContext ------------------------------------------------------------------

WoglacParser::LiteralExpressionContext::LiteralExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::NumericLiteral() {
  return getToken(WoglacParser::NumericLiteral, 0);
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::BlockLiteral() {
  return getToken(WoglacParser::BlockLiteral, 0);
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::BoolLiteral() {
  return getToken(WoglacParser::BoolLiteral, 0);
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::StringLiteral() {
  return getToken(WoglacParser::StringLiteral, 0);
}


size_t WoglacParser::LiteralExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleLiteralExpression;
}

void WoglacParser::LiteralExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpression(this);
}

void WoglacParser::LiteralExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpression(this);
}

WoglacParser::LiteralExpressionContext* WoglacParser::literalExpression() {
  LiteralExpressionContext *_localctx = _tracker.createInstance<LiteralExpressionContext>(_ctx, getState());
  enterRule(_localctx, 78, WoglacParser::RuleLiteralExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(492);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__27:
      case WoglacParser::T__35:
      case WoglacParser::NumericLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(486);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == WoglacParser::T__27

        || _la == WoglacParser::T__35) {
          setState(485);
          _la = _input->LA(1);
          if (!(_la == WoglacParser::T__27

          || _la == WoglacParser::T__35)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
        }
        setState(488);
        dynamic_cast<LiteralExpressionContext *>(_localctx)->num = match(WoglacParser::NumericLiteral);
        break;
      }

      case WoglacParser::BlockLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(489);
        dynamic_cast<LiteralExpressionContext *>(_localctx)->block = match(WoglacParser::BlockLiteral);
        break;
      }

      case WoglacParser::BoolLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(490);
        dynamic_cast<LiteralExpressionContext *>(_localctx)->bool_ = match(WoglacParser::BoolLiteral);
        break;
      }

      case WoglacParser::StringLiteral: {
        enterOuterAlt(_localctx, 4);
        setState(491);
        dynamic_cast<LiteralExpressionContext *>(_localctx)->string = match(WoglacParser::StringLiteral);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool WoglacParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 27: return andExpressionSempred(dynamic_cast<AndExpressionContext *>(context), predicateIndex);
    case 28: return orExpressionSempred(dynamic_cast<OrExpressionContext *>(context), predicateIndex);
    case 30: return addExpressionSempred(dynamic_cast<AddExpressionContext *>(context), predicateIndex);
    case 31: return multExpressionSempred(dynamic_cast<MultExpressionContext *>(context), predicateIndex);
    case 33: return inlineFunctionCallExpressionSempred(dynamic_cast<InlineFunctionCallExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool WoglacParser::andExpressionSempred(AndExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::orExpressionSempred(OrExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::addExpressionSempred(AddExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::multExpressionSempred(MultExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::inlineFunctionCallExpressionSempred(InlineFunctionCallExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> WoglacParser::_decisionToDFA;
atn::PredictionContextCache WoglacParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN WoglacParser::_atn;
std::vector<uint16_t> WoglacParser::_serializedATN;

std::vector<std::string> WoglacParser::_ruleNames = {
  "module", "statement", "scope", "contentOrSemicolon", "pragmaStatement", 
  "variableDefinition", "paramDefinition", "biomeParamDefinition", "paramSetStatement", 
  "biomeConditionStatement", "structureConditionStatement", "ruleExpansionStatement", 
  "componentNodeStatement", "componentNodeStatementCommonPart", "componentNodePropertiesSection", 
  "componentNodeOrientationExpression", "componentAreaStatement", "componentBlockStatement", 
  "componentIncludeStatement", "componentIncludeStatementParam", "componentIncludeStatementBlockParam", 
  "componentIncludeStatementNodeParam", "positionExpression", "expression", 
  "parentExpression", "ternaryExpression", "logicalExpression", "andExpression", 
  "orExpression", "comparisonExpression", "addExpression", "multExpression", 
  "unaryExpression", "inlineFunctionCallExpression", "atomicExpression", 
  "arugmentListExpression", "biomeParamExpression", "functionCallExpression", 
  "extendedIdentifier", "literalExpression"
};

std::vector<std::string> WoglacParser::_literalNames = {
  "", "'extend'", "'namespace'", "'rule'", "'component'", "'biome'", "'{'", 
  "'}'", "';'", "'pragma'", "'='", "'export'", "'param'", "'?='", "'condition'", 
  "'+-'", "'->'", "'::'", "'void'", "'!'", "':'", "'node'", "'('", "'|'", 
  "'-'", "')'", "'+'", "'area'", "'#'", "'?'", "'block'", "'include'", "','", 
  "'&&'", "'||'", "'.'", "'~'"
};

std::vector<std::string> WoglacParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "LineComment", "BlockComment", "Whitespace", "Type", "BlockLiteral", 
  "ComparisonOp", "BoolLiteral", "StringLiteral", "MultOp", "Identifier", 
  "NumericLiteral"
};

dfa::Vocabulary WoglacParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> WoglacParser::_tokenNames;

WoglacParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x31, 0x1f1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x3, 0x2, 0x7, 0x2, 0x54, 0xa, 0x2, 0xc, 0x2, 
    0xe, 0x2, 0x57, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x68, 0xa, 0x3, 0x3, 0x4, 
    0x5, 0x4, 0x6b, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x7, 0x4, 0x73, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x76, 0xb, 
    0x4, 0x3, 0x4, 0x5, 0x4, 0x79, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 
    0x7d, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x80, 0xb, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x5, 0x5, 0x84, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x5, 0x6, 0x8b, 0xa, 0x6, 0x5, 0x6, 0x8d, 0xa, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x7, 0x5, 0x7, 0x92, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x9c, 0xa, 
    0x8, 0x5, 0x8, 0x9e, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x5, 0x8, 0xa5, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0xb3, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xbd, 0xa, 
    0xb, 0x5, 0xb, 0xbf, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 
    0xcb, 0xa, 0xc, 0x5, 0xc, 0xcd, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xd5, 0xa, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xdd, 0xa, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xe1, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 
    0xd, 0xe5, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 
    0xeb, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x5, 
    0xf, 0xf2, 0xa, 0xf, 0x3, 0xf, 0x5, 0xf, 0xf5, 0xa, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x5, 0xf, 0xf9, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x5, 0x10, 0xff, 0xa, 0x10, 0x3, 0x10, 0x5, 0x10, 0x102, 0xa, 0x10, 
    0x3, 0x10, 0x5, 0x10, 0x105, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 
    0x109, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x112, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x119, 0xa, 0x12, 0x3, 0x12, 
    0x5, 0x12, 0x11c, 0xa, 0x12, 0x3, 0x12, 0x5, 0x12, 0x11f, 0xa, 0x12, 
    0x3, 0x12, 0x5, 0x12, 0x122, 0xa, 0x12, 0x3, 0x12, 0x5, 0x12, 0x125, 
    0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x12b, 
    0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x130, 0xa, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0x13b, 0xa, 0x14, 0xc, 0x14, 
    0xe, 0x14, 0x13e, 0xb, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 
    0x5, 0x15, 0x144, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x159, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x167, 0xa, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x16c, 0xa, 0x1b, 0x3, 0x1c, 
    0x3, 0x1c, 0x5, 0x1c, 0x170, 0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x7, 0x1d, 0x178, 0xa, 0x1d, 0xc, 0x1d, 
    0xe, 0x1d, 0x17b, 0xb, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x183, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 
    0x186, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
    0x5, 0x1f, 0x18d, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x7, 0x20, 0x195, 0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 
    0x198, 0xb, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x7, 0x21, 0x1a0, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x1a3, 
    0xb, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 
    0x22, 0x1aa, 0xa, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x7, 0x23, 0x1b3, 0xa, 0x23, 0xc, 0x23, 
    0xe, 0x23, 0x1b6, 0xb, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 
    0x3, 0x24, 0x5, 0x24, 0x1bd, 0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 
    0x3, 0x25, 0x7, 0x25, 0x1c3, 0xa, 0x25, 0xc, 0x25, 0xe, 0x25, 0x1c6, 
    0xb, 0x25, 0x3, 0x25, 0x5, 0x25, 0x1c9, 0xa, 0x25, 0x5, 0x25, 0x1cb, 
    0xa, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 
    0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x7, 0x26, 0x1d6, 0xa, 0x26, 
    0xc, 0x26, 0xe, 0x26, 0x1d9, 0xb, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x7, 0x28, 0x1e3, 
    0xa, 0x28, 0xc, 0x28, 0xe, 0x28, 0x1e6, 0xb, 0x28, 0x3, 0x29, 0x5, 0x29, 
    0x1e9, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 
    0x1ef, 0xa, 0x29, 0x3, 0x29, 0x2, 0x7, 0x38, 0x3a, 0x3e, 0x40, 0x44, 
    0x2a, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 
    0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 
    0x4a, 0x4c, 0x4e, 0x50, 0x2, 0x7, 0x3, 0x2, 0x4, 0x7, 0x3, 0x2, 0x5, 
    0x6, 0x3, 0x2, 0x5, 0x7, 0x4, 0x2, 0x1a, 0x1a, 0x1c, 0x1c, 0x4, 0x2, 
    0x1e, 0x1e, 0x26, 0x26, 0x2, 0x214, 0x2, 0x55, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x67, 0x3, 0x2, 0x2, 0x2, 0x6, 0x78, 0x3, 0x2, 0x2, 0x2, 0x8, 0x83, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x85, 0x3, 0x2, 0x2, 0x2, 0xc, 0x91, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x10, 0xa8, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0xb2, 0x3, 0x2, 0x2, 0x2, 0x14, 0xbe, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0xcc, 0x3, 0x2, 0x2, 0x2, 0x18, 0xd2, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0xea, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xf1, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xfc, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x22, 0x111, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x26, 0x135, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0x143, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x145, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x14b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x150, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x32, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x34, 
    0x16b, 0x3, 0x2, 0x2, 0x2, 0x36, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x38, 0x171, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x18c, 0x3, 
    0x2, 0x2, 0x2, 0x3e, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x199, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1ab, 0x3, 0x2, 0x2, 
    0x2, 0x46, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x48, 0x1be, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x1ce, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x4e, 
    0x1df, 0x3, 0x2, 0x2, 0x2, 0x50, 0x1ee, 0x3, 0x2, 0x2, 0x2, 0x52, 0x54, 
    0x5, 0x4, 0x3, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0x57, 0x3, 
    0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 0x2, 
    0x2, 0x2, 0x56, 0x58, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 
    0x2, 0x58, 0x59, 0x7, 0x2, 0x2, 0x3, 0x59, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x5a, 0x68, 0x5, 0xa, 0x6, 0x2, 0x5b, 0x68, 0x5, 0xe, 0x8, 0x2, 0x5c, 
    0x68, 0x5, 0x10, 0x9, 0x2, 0x5d, 0x68, 0x5, 0x12, 0xa, 0x2, 0x5e, 0x68, 
    0x5, 0x14, 0xb, 0x2, 0x5f, 0x68, 0x5, 0xc, 0x7, 0x2, 0x60, 0x68, 0x5, 
    0x18, 0xd, 0x2, 0x61, 0x68, 0x5, 0x6, 0x4, 0x2, 0x62, 0x68, 0x5, 0x1a, 
    0xe, 0x2, 0x63, 0x68, 0x5, 0x24, 0x13, 0x2, 0x64, 0x68, 0x5, 0x22, 0x12, 
    0x2, 0x65, 0x68, 0x5, 0x16, 0xc, 0x2, 0x66, 0x68, 0x5, 0x26, 0x14, 0x2, 
    0x67, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x67, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x67, 
    0x5c, 0x3, 0x2, 0x2, 0x2, 0x67, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x67, 0x5e, 
    0x3, 0x2, 0x2, 0x2, 0x67, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x67, 0x60, 0x3, 
    0x2, 0x2, 0x2, 0x67, 0x61, 0x3, 0x2, 0x2, 0x2, 0x67, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0x67, 0x63, 0x3, 0x2, 0x2, 0x2, 0x67, 0x64, 0x3, 0x2, 0x2, 
    0x2, 0x67, 0x65, 0x3, 0x2, 0x2, 0x2, 0x67, 0x66, 0x3, 0x2, 0x2, 0x2, 
    0x68, 0x5, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6b, 0x7, 0x3, 0x2, 0x2, 0x6a, 
    0x69, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 
    0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x9, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x5, 
    0x4e, 0x28, 0x2, 0x6e, 0x6f, 0x5, 0x8, 0x5, 0x2, 0x6f, 0x79, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0x74, 0x7, 0x8, 0x2, 0x2, 0x71, 0x73, 0x5, 0x4, 0x3, 
    0x2, 0x72, 0x71, 0x3, 0x2, 0x2, 0x2, 0x73, 0x76, 0x3, 0x2, 0x2, 0x2, 
    0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x3, 0x2, 0x2, 0x2, 0x75, 
    0x77, 0x3, 0x2, 0x2, 0x2, 0x76, 0x74, 0x3, 0x2, 0x2, 0x2, 0x77, 0x79, 
    0x7, 0x9, 0x2, 0x2, 0x78, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x78, 0x70, 0x3, 
    0x2, 0x2, 0x2, 0x79, 0x7, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7e, 0x7, 0x8, 
    0x2, 0x2, 0x7b, 0x7d, 0x5, 0x4, 0x3, 0x2, 0x7c, 0x7b, 0x3, 0x2, 0x2, 
    0x2, 0x7d, 0x80, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 
    0x7e, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x81, 0x3, 0x2, 0x2, 0x2, 0x80, 
    0x7e, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 0x7, 0x9, 0x2, 0x2, 0x82, 0x84, 
    0x7, 0xa, 0x2, 0x2, 0x83, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x83, 0x82, 0x3, 
    0x2, 0x2, 0x2, 0x84, 0x9, 0x3, 0x2, 0x2, 0x2, 0x85, 0x86, 0x7, 0xb, 
    0x2, 0x2, 0x86, 0x8c, 0x5, 0x4e, 0x28, 0x2, 0x87, 0x8a, 0x7, 0xc, 0x2, 
    0x2, 0x88, 0x8b, 0x5, 0x50, 0x29, 0x2, 0x89, 0x8b, 0x7, 0x30, 0x2, 0x2, 
    0x8a, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8b, 
    0x8d, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x87, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 
    0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x7, 
    0xa, 0x2, 0x2, 0x8f, 0xb, 0x3, 0x2, 0x2, 0x2, 0x90, 0x92, 0x7, 0xd, 
    0x2, 0x2, 0x91, 0x90, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 0x2, 
    0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x7, 0x2a, 0x2, 0x2, 
    0x94, 0x95, 0x5, 0x4e, 0x28, 0x2, 0x95, 0x96, 0x7, 0xc, 0x2, 0x2, 0x96, 
    0x97, 0x5, 0x30, 0x19, 0x2, 0x97, 0x98, 0x7, 0xa, 0x2, 0x2, 0x98, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x99, 0x9b, 0x9, 0x3, 0x2, 0x2, 0x9a, 0x9c, 0x5, 
    0x4e, 0x28, 0x2, 0x9b, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x3, 0x2, 
    0x2, 0x2, 0x9c, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x99, 0x3, 0x2, 0x2, 
    0x2, 0x9d, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x3, 0x2, 0x2, 0x2, 
    0x9f, 0xa0, 0x7, 0xe, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x2a, 0x2, 0x2, 0xa1, 
    0xa4, 0x7, 0x30, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0xf, 0x2, 0x2, 0xa3, 0xa5, 
    0x5, 0x30, 0x19, 0x2, 0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x3, 
    0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0xa, 
    0x2, 0x2, 0xa7, 0xf, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x7, 0x2, 
    0x2, 0xa9, 0xaa, 0x7, 0xe, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x2a, 0x2, 0x2, 
    0xab, 0xac, 0x5, 0x4e, 0x28, 0x2, 0xac, 0xad, 0x7, 0xf, 0x2, 0x2, 0xad, 
    0xae, 0x5, 0x30, 0x19, 0x2, 0xae, 0xaf, 0x7, 0xa, 0x2, 0x2, 0xaf, 0x11, 
    0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x9, 0x4, 0x2, 0x2, 0xb1, 0xb3, 0x5, 
    0x4e, 0x28, 0x2, 0xb2, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x3, 0x2, 
    0x2, 0x2, 0xb3, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0xe, 0x2, 
    0x2, 0xb5, 0xb6, 0x5, 0x4e, 0x28, 0x2, 0xb6, 0xb7, 0x7, 0xc, 0x2, 0x2, 
    0xb7, 0xb8, 0x5, 0x30, 0x19, 0x2, 0xb8, 0xb9, 0x7, 0xa, 0x2, 0x2, 0xb9, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbc, 0x7, 0x7, 0x2, 0x2, 0xbb, 0xbd, 
    0x5, 0x4e, 0x28, 0x2, 0xbc, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x3, 
    0x2, 0x2, 0x2, 0xbd, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xba, 0x3, 0x2, 
    0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x3, 0x2, 0x2, 
    0x2, 0xc0, 0xc1, 0x7, 0x10, 0x2, 0x2, 0xc1, 0xc2, 0x5, 0x4e, 0x28, 0x2, 
    0xc2, 0xc3, 0x7, 0xc, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x31, 0x2, 0x2, 0xc4, 
    0xc5, 0x7, 0x11, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0x31, 0x2, 0x2, 0xc6, 0xc7, 
    0x7, 0xa, 0x2, 0x2, 0xc7, 0x15, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xca, 0x9, 
    0x3, 0x2, 0x2, 0xc9, 0xcb, 0x5, 0x4e, 0x28, 0x2, 0xca, 0xc9, 0x3, 0x2, 
    0x2, 0x2, 0xca, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcd, 0x3, 0x2, 0x2, 
    0x2, 0xcc, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcd, 0x3, 0x2, 0x2, 0x2, 
    0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcf, 0x7, 0x10, 0x2, 0x2, 0xcf, 
    0xd0, 0x5, 0x30, 0x19, 0x2, 0xd0, 0xd1, 0x7, 0xa, 0x2, 0x2, 0xd1, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0xd2, 0xd4, 0x7, 0x5, 0x2, 0x2, 0xd3, 0xd5, 0x5, 
    0x4e, 0x28, 0x2, 0xd4, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd5, 0x3, 0x2, 
    0x2, 0x2, 0xd5, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xdc, 0x7, 0x12, 0x2, 
    0x2, 0xd7, 0xd8, 0x5, 0x4e, 0x28, 0x2, 0xd8, 0xd9, 0x7, 0x13, 0x2, 0x2, 
    0xd9, 0xda, 0x7, 0x30, 0x2, 0x2, 0xda, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xdb, 
    0xdd, 0x7, 0x14, 0x2, 0x2, 0xdc, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdb, 
    0x3, 0x2, 0x2, 0x2, 0xdd, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x7, 
    0x15, 0x2, 0x2, 0xdf, 0xe1, 0x7, 0x31, 0x2, 0x2, 0xe0, 0xde, 0x3, 0x2, 
    0x2, 0x2, 0xe0, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe4, 0x3, 0x2, 0x2, 
    0x2, 0xe2, 0xe3, 0x7, 0x16, 0x2, 0x2, 0xe3, 0xe5, 0x7, 0x31, 0x2, 0x2, 
    0xe4, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe5, 
    0xe6, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x5, 0x8, 0x5, 0x2, 0xe7, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x7, 0x6, 0x2, 0x2, 0xe9, 0xeb, 0x5, 
    0x4e, 0x28, 0x2, 0xea, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xea, 0xeb, 0x3, 0x2, 
    0x2, 0x2, 0xeb, 0xec, 0x3, 0x2, 0x2, 0x2, 0xec, 0xed, 0x7, 0x17, 0x2, 
    0x2, 0xed, 0xee, 0x5, 0x2e, 0x18, 0x2, 0xee, 0xef, 0x5, 0x1c, 0xf, 0x2, 
    0xef, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf2, 0x5, 0x1e, 0x10, 0x2, 0xf1, 
    0xf0, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf4, 
    0x3, 0x2, 0x2, 0x2, 0xf3, 0xf5, 0x7, 0x30, 0x2, 0x2, 0xf4, 0xf3, 0x3, 
    0x2, 0x2, 0x2, 0xf4, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf8, 0x3, 0x2, 
    0x2, 0x2, 0xf6, 0xf7, 0x7, 0x12, 0x2, 0x2, 0xf7, 0xf9, 0x5, 0x4e, 0x28, 
    0x2, 0xf8, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf9, 0x3, 0x2, 0x2, 0x2, 
    0xf9, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 0x5, 0x8, 0x5, 0x2, 0xfb, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xfe, 0x7, 0x18, 0x2, 0x2, 0xfd, 0xff, 
    0x7, 0xc, 0x2, 0x2, 0xfe, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xff, 0x3, 
    0x2, 0x2, 0x2, 0xff, 0x101, 0x3, 0x2, 0x2, 0x2, 0x100, 0x102, 0x7, 0x19, 
    0x2, 0x2, 0x101, 0x100, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x3, 0x2, 
    0x2, 0x2, 0x102, 0x104, 0x3, 0x2, 0x2, 0x2, 0x103, 0x105, 0x7, 0x1a, 
    0x2, 0x2, 0x104, 0x103, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 0x3, 0x2, 
    0x2, 0x2, 0x105, 0x106, 0x3, 0x2, 0x2, 0x2, 0x106, 0x108, 0x5, 0x20, 
    0x11, 0x2, 0x107, 0x109, 0x5, 0x20, 0x11, 0x2, 0x108, 0x107, 0x3, 0x2, 
    0x2, 0x2, 0x108, 0x109, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 0x3, 0x2, 
    0x2, 0x2, 0x10a, 0x10b, 0x7, 0x1b, 0x2, 0x2, 0x10b, 0x1f, 0x3, 0x2, 
    0x2, 0x2, 0x10c, 0x10d, 0x7, 0x30, 0x2, 0x2, 0x10d, 0x10e, 0x9, 0x5, 
    0x2, 0x2, 0x10e, 0x21, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x6, 0x2, 
    0x2, 0x110, 0x112, 0x5, 0x4e, 0x28, 0x2, 0x111, 0x10f, 0x3, 0x2, 0x2, 
    0x2, 0x111, 0x112, 0x3, 0x2, 0x2, 0x2, 0x112, 0x113, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0x114, 0x7, 0x1d, 0x2, 0x2, 0x114, 0x115, 0x5, 0x2e, 0x18, 
    0x2, 0x115, 0x121, 0x5, 0x2e, 0x18, 0x2, 0x116, 0x118, 0x7, 0x18, 0x2, 
    0x2, 0x117, 0x119, 0x7, 0x1e, 0x2, 0x2, 0x118, 0x117, 0x3, 0x2, 0x2, 
    0x2, 0x118, 0x119, 0x3, 0x2, 0x2, 0x2, 0x119, 0x11b, 0x3, 0x2, 0x2, 
    0x2, 0x11a, 0x11c, 0x7, 0x15, 0x2, 0x2, 0x11b, 0x11a, 0x3, 0x2, 0x2, 
    0x2, 0x11b, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11e, 0x3, 0x2, 0x2, 
    0x2, 0x11d, 0x11f, 0x7, 0x1f, 0x2, 0x2, 0x11e, 0x11d, 0x3, 0x2, 0x2, 
    0x2, 0x11e, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x120, 0x3, 0x2, 0x2, 
    0x2, 0x120, 0x122, 0x7, 0x1b, 0x2, 0x2, 0x121, 0x116, 0x3, 0x2, 0x2, 
    0x2, 0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 0x124, 0x3, 0x2, 0x2, 
    0x2, 0x123, 0x125, 0x7, 0x30, 0x2, 0x2, 0x124, 0x123, 0x3, 0x2, 0x2, 
    0x2, 0x124, 0x125, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x3, 0x2, 0x2, 
    0x2, 0x126, 0x127, 0x7, 0xa, 0x2, 0x2, 0x127, 0x23, 0x3, 0x2, 0x2, 0x2, 
    0x128, 0x129, 0x7, 0x6, 0x2, 0x2, 0x129, 0x12b, 0x5, 0x4e, 0x28, 0x2, 
    0x12a, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 0x3, 0x2, 0x2, 0x2, 
    0x12b, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12d, 0x7, 0x20, 0x2, 0x2, 
    0x12d, 0x12f, 0x5, 0x2e, 0x18, 0x2, 0x12e, 0x130, 0x5, 0x2e, 0x18, 0x2, 
    0x12f, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x130, 0x3, 0x2, 0x2, 0x2, 
    0x130, 0x131, 0x3, 0x2, 0x2, 0x2, 0x131, 0x132, 0x7, 0xc, 0x2, 0x2, 
    0x132, 0x133, 0x5, 0x30, 0x19, 0x2, 0x133, 0x134, 0x7, 0xa, 0x2, 0x2, 
    0x134, 0x25, 0x3, 0x2, 0x2, 0x2, 0x135, 0x136, 0x7, 0x6, 0x2, 0x2, 0x136, 
    0x137, 0x7, 0x21, 0x2, 0x2, 0x137, 0x138, 0x7, 0x2e, 0x2, 0x2, 0x138, 
    0x13c, 0x7, 0x8, 0x2, 0x2, 0x139, 0x13b, 0x5, 0x28, 0x15, 0x2, 0x13a, 
    0x139, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x13c, 
    0x13a, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13d, 
    0x13f, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x13f, 
    0x140, 0x7, 0x9, 0x2, 0x2, 0x140, 0x27, 0x3, 0x2, 0x2, 0x2, 0x141, 0x144, 
    0x5, 0x2a, 0x16, 0x2, 0x142, 0x144, 0x5, 0x2c, 0x17, 0x2, 0x143, 0x141, 
    0x3, 0x2, 0x2, 0x2, 0x143, 0x142, 0x3, 0x2, 0x2, 0x2, 0x144, 0x29, 0x3, 
    0x2, 0x2, 0x2, 0x145, 0x146, 0x7, 0x31, 0x2, 0x2, 0x146, 0x147, 0x7, 
    0x12, 0x2, 0x2, 0x147, 0x148, 0x7, 0x20, 0x2, 0x2, 0x148, 0x149, 0x5, 
    0x30, 0x19, 0x2, 0x149, 0x14a, 0x7, 0xa, 0x2, 0x2, 0x14a, 0x2b, 0x3, 
    0x2, 0x2, 0x2, 0x14b, 0x14c, 0x7, 0x31, 0x2, 0x2, 0x14c, 0x14d, 0x7, 
    0x12, 0x2, 0x2, 0x14d, 0x14e, 0x7, 0x17, 0x2, 0x2, 0x14e, 0x14f, 0x5, 
    0x1c, 0xf, 0x2, 0x14f, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x150, 0x158, 0x7, 
    0x18, 0x2, 0x2, 0x151, 0x152, 0x5, 0x30, 0x19, 0x2, 0x152, 0x153, 0x7, 
    0x22, 0x2, 0x2, 0x153, 0x154, 0x5, 0x30, 0x19, 0x2, 0x154, 0x155, 0x7, 
    0x22, 0x2, 0x2, 0x155, 0x156, 0x5, 0x30, 0x19, 0x2, 0x156, 0x159, 0x3, 
    0x2, 0x2, 0x2, 0x157, 0x159, 0x5, 0x30, 0x19, 0x2, 0x158, 0x151, 0x3, 
    0x2, 0x2, 0x2, 0x158, 0x157, 0x3, 0x2, 0x2, 0x2, 0x159, 0x15a, 0x3, 
    0x2, 0x2, 0x2, 0x15a, 0x15b, 0x7, 0x1b, 0x2, 0x2, 0x15b, 0x2f, 0x3, 
    0x2, 0x2, 0x2, 0x15c, 0x15d, 0x5, 0x34, 0x1b, 0x2, 0x15d, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0x15e, 0x15f, 0x7, 0x18, 0x2, 0x2, 0x15f, 0x160, 0x5, 
    0x30, 0x19, 0x2, 0x160, 0x161, 0x7, 0x1b, 0x2, 0x2, 0x161, 0x33, 0x3, 
    0x2, 0x2, 0x2, 0x162, 0x16c, 0x5, 0x36, 0x1c, 0x2, 0x163, 0x164, 0x5, 
    0x36, 0x1c, 0x2, 0x164, 0x166, 0x7, 0x1f, 0x2, 0x2, 0x165, 0x167, 0x5, 
    0x36, 0x1c, 0x2, 0x166, 0x165, 0x3, 0x2, 0x2, 0x2, 0x166, 0x167, 0x3, 
    0x2, 0x2, 0x2, 0x167, 0x168, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x7, 
    0x16, 0x2, 0x2, 0x169, 0x16a, 0x5, 0x34, 0x1b, 0x2, 0x16a, 0x16c, 0x3, 
    0x2, 0x2, 0x2, 0x16b, 0x162, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x163, 0x3, 
    0x2, 0x2, 0x2, 0x16c, 0x35, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x170, 0x5, 0x38, 
    0x1d, 0x2, 0x16e, 0x170, 0x5, 0x3a, 0x1e, 0x2, 0x16f, 0x16d, 0x3, 0x2, 
    0x2, 0x2, 0x16f, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x170, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x171, 0x172, 0x8, 0x1d, 0x1, 0x2, 0x172, 0x173, 0x5, 0x3c, 0x1f, 
    0x2, 0x173, 0x179, 0x3, 0x2, 0x2, 0x2, 0x174, 0x175, 0xc, 0x3, 0x2, 
    0x2, 0x175, 0x176, 0x7, 0x23, 0x2, 0x2, 0x176, 0x178, 0x5, 0x3c, 0x1f, 
    0x2, 0x177, 0x174, 0x3, 0x2, 0x2, 0x2, 0x178, 0x17b, 0x3, 0x2, 0x2, 
    0x2, 0x179, 0x177, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17a, 0x3, 0x2, 0x2, 
    0x2, 0x17a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x179, 0x3, 0x2, 0x2, 0x2, 
    0x17c, 0x17d, 0x8, 0x1e, 0x1, 0x2, 0x17d, 0x17e, 0x5, 0x3c, 0x1f, 0x2, 
    0x17e, 0x184, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x180, 0xc, 0x3, 0x2, 0x2, 
    0x180, 0x181, 0x7, 0x24, 0x2, 0x2, 0x181, 0x183, 0x5, 0x3c, 0x1f, 0x2, 
    0x182, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x183, 0x186, 0x3, 0x2, 0x2, 0x2, 
    0x184, 0x182, 0x3, 0x2, 0x2, 0x2, 0x184, 0x185, 0x3, 0x2, 0x2, 0x2, 
    0x185, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x186, 0x184, 0x3, 0x2, 0x2, 0x2, 0x187, 
    0x18d, 0x5, 0x3e, 0x20, 0x2, 0x188, 0x189, 0x5, 0x3e, 0x20, 0x2, 0x189, 
    0x18a, 0x7, 0x2c, 0x2, 0x2, 0x18a, 0x18b, 0x5, 0x3e, 0x20, 0x2, 0x18b, 
    0x18d, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x187, 0x3, 0x2, 0x2, 0x2, 0x18c, 
    0x188, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x18f, 
    0x8, 0x20, 0x1, 0x2, 0x18f, 0x190, 0x5, 0x40, 0x21, 0x2, 0x190, 0x196, 
    0x3, 0x2, 0x2, 0x2, 0x191, 0x192, 0xc, 0x3, 0x2, 0x2, 0x192, 0x193, 
    0x9, 0x5, 0x2, 0x2, 0x193, 0x195, 0x5, 0x40, 0x21, 0x2, 0x194, 0x191, 
    0x3, 0x2, 0x2, 0x2, 0x195, 0x198, 0x3, 0x2, 0x2, 0x2, 0x196, 0x194, 
    0x3, 0x2, 0x2, 0x2, 0x196, 0x197, 0x3, 0x2, 0x2, 0x2, 0x197, 0x3f, 0x3, 
    0x2, 0x2, 0x2, 0x198, 0x196, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19a, 0x8, 
    0x21, 0x1, 0x2, 0x19a, 0x19b, 0x5, 0x42, 0x22, 0x2, 0x19b, 0x1a1, 0x3, 
    0x2, 0x2, 0x2, 0x19c, 0x19d, 0xc, 0x3, 0x2, 0x2, 0x19d, 0x19e, 0x7, 
    0x2f, 0x2, 0x2, 0x19e, 0x1a0, 0x5, 0x42, 0x22, 0x2, 0x19f, 0x19c, 0x3, 
    0x2, 0x2, 0x2, 0x1a0, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x19f, 0x3, 
    0x2, 0x2, 0x2, 0x1a1, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0x1a3, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1aa, 0x5, 0x44, 
    0x23, 0x2, 0x1a5, 0x1a6, 0x9, 0x5, 0x2, 0x2, 0x1a6, 0x1aa, 0x5, 0x44, 
    0x23, 0x2, 0x1a7, 0x1a8, 0x7, 0x15, 0x2, 0x2, 0x1a8, 0x1aa, 0x5, 0x44, 
    0x23, 0x2, 0x1a9, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1a5, 0x3, 0x2, 
    0x2, 0x2, 0x1a9, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x43, 0x3, 0x2, 0x2, 
    0x2, 0x1ab, 0x1ac, 0x8, 0x23, 0x1, 0x2, 0x1ac, 0x1ad, 0x5, 0x46, 0x24, 
    0x2, 0x1ad, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1af, 0xc, 0x3, 0x2, 
    0x2, 0x1af, 0x1b0, 0x7, 0x13, 0x2, 0x2, 0x1b0, 0x1b1, 0x7, 0x30, 0x2, 
    0x2, 0x1b1, 0x1b3, 0x5, 0x48, 0x25, 0x2, 0x1b2, 0x1ae, 0x3, 0x2, 0x2, 
    0x2, 0x1b3, 0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b2, 0x3, 0x2, 0x2, 
    0x2, 0x1b4, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x45, 0x3, 0x2, 0x2, 0x2, 
    0x1b6, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1bd, 0x5, 0x4c, 0x27, 0x2, 
    0x1b8, 0x1bd, 0x5, 0x50, 0x29, 0x2, 0x1b9, 0x1bd, 0x5, 0x32, 0x1a, 0x2, 
    0x1ba, 0x1bd, 0x5, 0x4a, 0x26, 0x2, 0x1bb, 0x1bd, 0x5, 0x4e, 0x28, 0x2, 
    0x1bc, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1b8, 0x3, 0x2, 0x2, 0x2, 
    0x1bc, 0x1b9, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1ba, 0x3, 0x2, 0x2, 0x2, 
    0x1bc, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1be, 
    0x1ca, 0x7, 0x18, 0x2, 0x2, 0x1bf, 0x1c4, 0x5, 0x30, 0x19, 0x2, 0x1c0, 
    0x1c1, 0x7, 0x22, 0x2, 0x2, 0x1c1, 0x1c3, 0x5, 0x30, 0x19, 0x2, 0x1c2, 
    0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c4, 
    0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c5, 
    0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1c4, 0x3, 0x2, 0x2, 0x2, 0x1c7, 
    0x1c9, 0x7, 0x22, 0x2, 0x2, 0x1c8, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x1c8, 
    0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1c9, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1ca, 
    0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1cb, 
    0x1cc, 0x3, 0x2, 0x2, 0x2, 0x1cc, 0x1cd, 0x7, 0x1b, 0x2, 0x2, 0x1cd, 
    0x49, 0x3, 0x2, 0x2, 0x2, 0x1ce, 0x1cf, 0x7, 0x7, 0x2, 0x2, 0x1cf, 0x1d0, 
    0x7, 0x18, 0x2, 0x2, 0x1d0, 0x1d1, 0x5, 0x4e, 0x28, 0x2, 0x1d1, 0x1d2, 
    0x7, 0x22, 0x2, 0x2, 0x1d2, 0x1d7, 0x7, 0x30, 0x2, 0x2, 0x1d3, 0x1d4, 
    0x7, 0x22, 0x2, 0x2, 0x1d4, 0x1d6, 0x5, 0x30, 0x19, 0x2, 0x1d5, 0x1d3, 
    0x3, 0x2, 0x2, 0x2, 0x1d6, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1d5, 
    0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1d8, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1da, 
    0x3, 0x2, 0x2, 0x2, 0x1d9, 0x1d7, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1db, 
    0x7, 0x1b, 0x2, 0x2, 0x1db, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1dd, 
    0x7, 0x30, 0x2, 0x2, 0x1dd, 0x1de, 0x5, 0x48, 0x25, 0x2, 0x1de, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e4, 0x7, 0x30, 0x2, 0x2, 0x1e0, 0x1e1, 
    0x7, 0x25, 0x2, 0x2, 0x1e1, 0x1e3, 0x7, 0x30, 0x2, 0x2, 0x1e2, 0x1e0, 
    0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e4, 0x1e2, 
    0x3, 0x2, 0x2, 0x2, 0x1e4, 0x1e5, 0x3, 0x2, 0x2, 0x2, 0x1e5, 0x4f, 0x3, 
    0x2, 0x2, 0x2, 0x1e6, 0x1e4, 0x3, 0x2, 0x2, 0x2, 0x1e7, 0x1e9, 0x9, 
    0x6, 0x2, 0x2, 0x1e8, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e9, 0x3, 
    0x2, 0x2, 0x2, 0x1e9, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1ef, 0x7, 
    0x31, 0x2, 0x2, 0x1eb, 0x1ef, 0x7, 0x2b, 0x2, 0x2, 0x1ec, 0x1ef, 0x7, 
    0x2d, 0x2, 0x2, 0x1ed, 0x1ef, 0x7, 0x2e, 0x2, 0x2, 0x1ee, 0x1e8, 0x3, 
    0x2, 0x2, 0x2, 0x1ee, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ec, 0x3, 
    0x2, 0x2, 0x2, 0x1ee, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x1ef, 0x51, 0x3, 0x2, 
    0x2, 0x2, 0x3d, 0x55, 0x67, 0x6a, 0x74, 0x78, 0x7e, 0x83, 0x8a, 0x8c, 
    0x91, 0x9b, 0x9d, 0xa4, 0xb2, 0xbc, 0xbe, 0xca, 0xcc, 0xd4, 0xdc, 0xe0, 
    0xe4, 0xea, 0xf1, 0xf4, 0xf8, 0xfe, 0x101, 0x104, 0x108, 0x111, 0x118, 
    0x11b, 0x11e, 0x121, 0x124, 0x12a, 0x12f, 0x13c, 0x143, 0x158, 0x166, 
    0x16b, 0x16f, 0x179, 0x184, 0x18c, 0x196, 0x1a1, 0x1a9, 0x1b4, 0x1bc, 
    0x1c4, 0x1c8, 0x1ca, 0x1d7, 0x1e4, 0x1e8, 0x1ee, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

WoglacParser::Initializer WoglacParser::_init;
