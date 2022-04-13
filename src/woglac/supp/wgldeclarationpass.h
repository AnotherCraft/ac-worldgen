#pragma once

// Must place before everything else because of antlr
#include "wglinclude.h"

#include "wglpass.h"

class WGLDeclarationPass : public WGLPass {

protected:
	virtual void enterScope(WoglacParser::ScopeContext *ctx) override;
	virtual void exitScope(WoglacParser::ScopeContext *ctx) override;

	virtual void enterRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) override;
	virtual void exitRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) override;

	virtual void enterParamDefinition(WoglacParser::ParamDefinitionContext *ctx) override;
	virtual void enterBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext *ctx) override;
	virtual void enterVariableDefinition(WoglacParser::VariableDefinitionContext *ctx) override;

	virtual void enterComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) override;
	virtual void exitComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) override;

	virtual void enterComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) override;
	virtual void exitComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) override;

};

