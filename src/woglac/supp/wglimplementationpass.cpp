#include "wglimplementationpass.h"

#include "util/iterators.h"

#include "../wglcompiler.h"

#include "wglerror.h"

#define EXPRESSION_RESULT(resultType, expr) ExpressionResult{ [=] (WGLAPIContext &ctx) { return (expr); }, resultType }

void WGLImplementationPass::enterScope(WoglacParser::ScopeContext *ctx) {
	WGLSymbol *sym = ctx_->astSymbolMapping.at(ctx);
	ASSERT(sym);

	currentScope_.push(sym);

	if(!ctx->extend) {
		switch(sym->symbolType()) {

			case SymbolType::Namespace:
			case SymbolType::Scope:
				break;

			case SymbolType::Biome:
				ctx_->addApiCmd(sym, {}, [sym](WGLAPIContext &ctx) {
					ctx.addSymbolMapping(sym, ctx.api->newBiome());
				});
				break;

			case SymbolType::Rule:
				ctx_->addApiCmd(sym, {}, [sym](WGLAPIContext &ctx) {
					ctx.addSymbolMapping(sym, ctx.api->newRule());
				});
				break;

			case SymbolType::Component:
				ctx_->addApiCmd(sym, {}, [sym](WGLAPIContext &ctx) {
					ctx.addSymbolMapping(sym, ctx.api->newComponent());
				});
				break;

			default:
				// Should not happen
				throw;

		}
	}
}

void WGLImplementationPass::exitScope(WoglacParser::ScopeContext *ctx) {
	popScope(ctx);
}

void WGLImplementationPass::enterRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) {
	WGLSymbol *sym = ctx_->astSymbolMapping.at(ctx);
	ASSERT(sym);

	currentScope_.push(sym);

	WGLSymbol *parentRule = sym->parent()->effectiveTarget();

	bool expandsToComponent = ctx->node;
	const std::string node = ctx->node ? WGLUtils::identifier(ctx->node) : std::string{};
	WGLSymbol *target = ctx->expansionTarget ? lookupIdentifier(ctx->expansionTarget, false) : nullptr;

	if(!target) {}
	else if(expandsToComponent && target->symbolType() != SymbolType::Component)
		throw WGLError(std::format("Symbol '{}' is not a structure component.", target->fullName()), ctx->target);
	else if(!expandsToComponent && target->symbolType() != SymbolType::Rule)
		throw WGLError(std::format("Symbol '{}' is not a structure rule.", target->fullName()), ctx->target);

	std::vector<std::pair<std::string, WGA_Symbol::PragmaValue >> pragmaSets;

	if(ctx->priority)
		pragmaSets.push_back({"priority", WGLUtils::numericLiteral(ctx->priority)});

	if(ctx->probabilityRatio)
		pragmaSets.push_back({"probabilityRatio", WGLUtils::numericLiteral(ctx->probabilityRatio)});

	ctx_->addApiCmd(sym, {parentRule, target}, [sym, parentRule, target, expandsToComponent, node, pragmaSets](WGLAPIContext &ctx) {
		WGA_RuleExpansion *rex;

		if(!target)
			rex = ctx.api->newRuleExpansion(ctx.map<WGA_Rule>(parentRule));
		else if(expandsToComponent)
			rex = ctx.api->newRuleExpansion(ctx.map<WGA_Rule>(parentRule), ctx.map<WGA_Component>(target), node);
		else
			rex = ctx.api->newRuleExpansion(ctx.map<WGA_Rule>(parentRule), ctx.map<WGA_Rule>(target));

		for(const auto &ps: pragmaSets)
			rex->setPragma(ps.first, ps.second);

		ctx.addSymbolMapping(sym, rex);
	});
}

void WGLImplementationPass::exitRuleExpansionStatement(WoglacParser::RuleExpansionStatementContext *ctx) {
	popScope(ctx);
}

void WGLImplementationPass::enterBiomeParamDefinition(WoglacParser::BiomeParamDefinitionContext *ctx) {
	WGLSymbol *sym = ctx_->astSymbolMapping.at(ctx);
	ASSERT(sym);

	DependencyList deps;
	auto val = expression(ctx->defaultValue, deps);

	ctx_->addApiCmd(sym, deps, [sym, val](WGLAPIContext &ctx) {
		// We use proxy to prevent problems when having multiple biome params with the same default value (or when overriding the default value with the actual default value expression)
		auto vf = val.func(ctx);
		vf->setDescription("PROXY:" + sym->desc());
		ctx.addSymbolMapping(sym, ctx.api->proxy(vf));
	});
}

void WGLImplementationPass::enterBiomeConditionStatement(WoglacParser::BiomeConditionStatementContext *ctx) {
	WGLSymbol *target = lookupIdentifier(ctx->target, false)->effectiveTarget();
	if(target->symbolType() != SymbolType::Biome)
		throw WGLError(std::format("Symbol '{}' is not a biome (biome condition syntax used).", target->fullName()), ctx->target);

	WGLSymbol *param = lookupIdentifier(ctx->param, false);
	if(param->symbolType() != SymbolType::FieldVariable)
		throw WGLError(std::format("Symbol '{}' is not a field variable (biome condition syntax used).", param->fullName()), ctx->param);

	const float mean = WGLUtils::numericLiteral(ctx->mean);
	const float dev = WGLUtils::numericLiteral(ctx->dev);

	ctx_->addApiCmd(nullptr, {target, param}, [target, param, mean, dev](WGLAPIContext &ctx) {
		ctx.map<WGA_Biome>(target)->addCondition(WGA_Biome::Condition{ctx.map<WGA_Value>(param), mean, dev});
	});
}

void WGLImplementationPass::enterVariableDefinition(WoglacParser::VariableDefinitionContext *ctx) {
	WGLSymbol *sym = ctx_->astSymbolMapping.at(ctx);
	ASSERT(sym);

	DependencyList deps;
	auto val = expression(ctx->val, deps);

	if(val.type != sym->valueType)
		throw WGLError(std::format("Variable '{}' is defined as type '{}' but the value expression is of type '{}'.", sym->fullName(), WGA_Value::typeNames.at(sym->valueType), WGA_Value::typeNames.at(val.type)), ctx);

	ctx_->addApiCmd(sym, deps, [sym, val](WGLAPIContext &ctx) {
		ctx.addSymbolMapping(sym, val.func(ctx));
	});
}

void WGLImplementationPass::enterParamDefinition(WoglacParser::ParamDefinitionContext *ctx) {
	WGLSymbol *sym = ctx_->astSymbolMapping.at(ctx);
	ASSERT(sym);

	WGLSymbol *parent = sym->parent()->effectiveTarget();

	DependencyList deps{
		parent
	};
	auto defaultValue = ctx->defaultValue ? expression(ctx->defaultValue, deps) : ExpressionResult();

	if(defaultValue.type != sym->valueType)
		throw WGLError(std::format("Structure parameter '{}' is defined as type '{}' but the default value expression is of type '{}'.", sym->fullName(), WGA_Value::typeNames.at(sym->valueType), WGA_Value::typeNames.at(defaultValue.type)), ctx);

	ctx_->addApiCmd(sym, deps, [sym, parent, defaultValue](WGLAPIContext &ctx) {
		ctx.addSymbolMapping(sym, ctx.api->grammarSymbolParam(ctx.map<WGA_GrammarSymbol>(parent), sym->name(), sym->valueType, defaultValue.func ? defaultValue.func(ctx) : nullptr));
	});
}

void WGLImplementationPass::enterParamSetStatement(WoglacParser::ParamSetStatementContext *ctx) {
	WGLSymbol *target = lookupIdentifier(ctx->target, false);
	WGLSymbol *effectiveTarget = target->effectiveTarget();
	const SymbolType targetType = effectiveTarget->symbolType();

	checkTargetTypeMatch(ctx->targetType, effectiveTarget, ctx);

	DependencyList deps{
		target
	};
	auto val = expression(ctx->value, deps);

	if(targetType == SymbolType::Biome) {
		WGLSymbol *param = lookupIdentifier(ctx->param, false);
		deps.insert(param);

		if(param->symbolType() != SymbolType::BiomeParam)
			throw WGLError(std::format("Symbol '{}' is not a biome param.", param->fullName()), ctx);

		if(val.type != param->valueType)
			throw WGLError(std::format("Biome param '{}' is of type '{}', but type '{}' provided in the specification for biome '{}'.", param->fullName(), WGA_Value::typeNames.at(param->valueType), WGA_Value::typeNames.at(val.type), target->fullName()), ctx);

		ctx_->addApiCmd(nullptr, deps, [target, param, val](WGLAPIContext &ctx) {
			ctx.map<WGA_Biome>(target)->setParam(ctx.map<WGA_Value>(param), val.func(ctx));
		});
	}
	else if(targetType == SymbolType::Rule || targetType == SymbolType::RuleExpansion ||
	        targetType == SymbolType::Component) {
		if(ctx->param->id.size() != 1)
			throw WGLError("Extended identifier params are only allowed for biomes.", ctx->param);

		const std::string paramName = WGLUtils::identifier(ctx->param->id[0]);

		ctx_->addApiCmd(nullptr, deps, [target, paramName, val](WGLAPIContext &ctx) {
			ctx.map<WGA_GrammarSymbol>(target)->setParam(paramName, val.func(ctx));
		});
	}
	else
		throw WGLError("Param set statements are allowed only for biome, rule, component and rule expansion targets.", ctx);
}

void WGLImplementationPass::enterComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) {
	WGLSymbol *component = lookupIdentifier(ctx->target, false)->effectiveTarget();
	WGLSymbol *sym = ctx_->astSymbolMapping[ctx->cmn];

	DependencyList deps{
		component
	};
	ExpressionResult pos = positionExpression(ctx->pos, deps);

	componentNodeCommonPart(sym, ctx->cmn, component, deps, [pos](WGLAPIContext &ctx, WGA_ComponentNode::Config &cfg) {
		cfg.position = pos.func(ctx);
	});

	currentScope_.push(sym);
}

void WGLImplementationPass::exitComponentNodeStatement(WoglacParser::ComponentNodeStatementContext *ctx) {
	popScope(ctx->cmn);
}

void WGLImplementationPass::enterComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) {
	WGLSymbol *sym = ctx_->astSymbolMapping[ctx];

	ASSERT(voxParser_.isEmpty());
	voxParser_.parseFile(ctx_->compiler->lookupFile(WGLUtils::stringLiteral(ctx->file), ctx));

	currentScope_.push(sym);
}

void WGLImplementationPass::exitComponentIncludeStatement(WoglacParser::ComponentIncludeStatementContext *ctx) {
	voxParser_.clear();

	popScope(ctx);
}

void WGLImplementationPass::enterComponentIncludeStatementBlockParam(WoglacParser::ComponentIncludeStatementBlockParamContext *ctx) {
	WGLSymbol *component = currentScope()->effectiveTarget();
	ASSERT(component->symbolType() == SymbolType::Component);

	const int id = WGLUtils::numericLiteral(ctx->id);
	if(!voxParser_.voxels().contains(id)) {
		std::cerr << std::format("Vox file '{}' does not contain voxels of ID {}", voxParser_.fileName(), id);
		return;
	}

	DependencyList deps;
	const auto val = expression(ctx->val, deps);

	std::vector<BlockWorldPos> poss;
	for(const VOXParser::VoxelPos &vp: voxParser_.voxels().at(id))
		poss.push_back(BlockWorldPos(vp.x, vp.y, vp.z));

	if(poss.empty())
		return;

	ctx_->addApiCmd(nullptr, deps, [component, val, poss](WGLAPIContext &ctx) {
		WGA_Component::Blocks blocks;
		blocks.block = val.func(ctx);
		blocks.positions = poss;

		ctx.map<WGA_Component>(component)->addBlocks(blocks);
	});
}

void WGLImplementationPass::enterComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext *ctx) {
	WGLSymbol *component = currentScope()->effectiveTarget();
	ASSERT(component->symbolType() == SymbolType::Component);

	const int id = WGLUtils::numericLiteral(ctx->id);

	componentIncludePositions_.clear();
	for(const VOXParser::VoxelPos &vp: voxParser_.voxels().at(id))
		componentIncludePositions_.push_back(BlockWorldPos(vp.x, vp.y, vp.z));

	if(componentIncludePositions_.empty())
		return;

	DependencyList deps;

	WGLSymbol *node = componentNodeDeclaration(ctx->com, currentScope());
	componentNodeCommonPart(node, ctx->com, component, deps, [pos = *componentIncludePositions_.begin()](WGLAPIContext &ctx, WGA_ComponentNode::Config &cfg) {
		cfg.position = ctx.api->constFloat3(pos.to<float>());
	});

	currentScope_.push(node);
}

void WGLImplementationPass::exitComponentIncludeStatementNodeParam(WoglacParser::ComponentIncludeStatementNodeParamContext *ctx) {
	if(componentIncludePositions_.empty())
		return;

	popScope(ctx->com);

	WGLSymbol *sourceNode = ctx_->astSymbolMapping[ctx->com];

	// Create all the other nodes, copy pragmas
	componentIncludePositions_.erase(componentIncludePositions_.begin());
	for(const BlockWorldPos &pos: componentIncludePositions_) {
		WGLSymbol *node = componentNodeDeclaration(ctx->com, currentScope(), false);
		DependencyList deps;

		componentNodeCommonPart(node, ctx->com, sourceNode->parent()->effectiveTarget(), deps, [pos](WGLAPIContext &ctx, WGA_ComponentNode::Config &cfg) {
			cfg.position = ctx.api->constFloat3(pos.to<float>());
		});

		ctx_->addApiCmd(nullptr, {}, [sourceNode, node](WGLAPIContext &ctx) {
			ctx.map<WGA_ComponentNode>(node)->setPragmas(ctx.map<WGA_ComponentNode>(sourceNode)->pragmas());
		});
	}
}

void WGLImplementationPass::enterComponentAreaStatement(WoglacParser::ComponentAreaStatementContext *ctx) {
	WGLSymbol *component = lookupIdentifier(ctx->target, false)->effectiveTarget();

	if(component->symbolType() != SymbolType::Component)
		throw WGLError("Node statements are allowed only in structure components.", ctx);

	DependencyList deps{
		component
	};
	ExpressionResult startPos = positionExpression(ctx->startPos, deps);
	ExpressionResult endPos = positionExpression(ctx->endPos, deps);

	const WGA_Component::Area iarea{
		.name = WGLUtils::identifier(ctx->name),
		.canOverlap = static_cast<bool>(ctx->canOverlap),
		.mustOverlap = static_cast<bool>(ctx->mustOverlap),
		.isVirtual = static_cast<bool>(ctx->isVirtual),
	};

	ctx_->addApiCmd(nullptr, deps, [component, startPos, endPos, iarea](WGLAPIContext &ctx) {
		WGA_Component::Area area = iarea;
		area.startPos = startPos.func(ctx);
		area.endPos = endPos.func(ctx);

		ctx.map<WGA_Component>(component)->addArea(area);
	});
}

void WGLImplementationPass::enterComponentBlockStatement(WoglacParser::ComponentBlockStatementContext *ctx) {
	WGLSymbol *component = lookupIdentifier(ctx->target, false)->effectiveTarget();

	if(component->symbolType() != SymbolType::Component)
		throw WGLError("Node statements are allowed only in structure components.", ctx);

	DependencyList deps{
		component
	};
	ExpressionResult startPos = positionExpression(ctx->startPos, deps);
	ExpressionResult endPos = ctx->endPos ? positionExpression(ctx->endPos, deps) : ExpressionResult();

	ExpressionResult value = expression(ctx->val, deps);
	if(value.type != ValueType::Block)
		throw WGLError(std::format("Structure block statement value expression must be of type 'Block', but '%1' was provided.", WGA_Value::typeNames.at(value.type)), ctx->val);

	ctx_->addApiCmd(nullptr, deps, [component, startPos, endPos, value](WGLAPIContext &ctx) {
		WGA_Component::Blocks area;
		area.startPos = startPos.func(ctx);
		area.endPos = endPos.func ? endPos.func(ctx) : nullptr;
		area.block = value.func(ctx);

		ctx.map<WGA_Component>(component)->addBlocks(area);
	});
}

void WGLImplementationPass::enterStructureConditionStatement(WoglacParser::StructureConditionStatementContext *ctx) {
	static const std::unordered_set<int> allowedSymbolTypes{
		+SymbolType::Component, +SymbolType::Rule, +SymbolType::RuleExpansion
	};

	WGLSymbol *target = lookupIdentifier(ctx->target, false)->effectiveTarget();

	if(!allowedSymbolTypes.contains(+target->symbolType()))
		throw WGLError("Conditions using this syntax are allowed only in structure rules/components/rule expansions.", ctx);

	DependencyList deps{
		target
	};
	ExpressionResult val = expression(ctx->cond, deps);

	if(val.type != ValueType::Bool)
		throw WGLError(std::format("Condition statement requires expression of type Bool, {} provided", WGA_Value::typeNames.at(val.type)), ctx);

	ctx_->addApiCmd(nullptr, deps, [target, val](WGLAPIContext &ctx) {
		WGA_GrammarSymbol::Condition cond;
		cond.value = val.func(ctx);

		ctx.map<WGA_GrammarSymbol>(target)->addCondition(cond);
	});
}

void WGLImplementationPass::enterPragmaStatement(WoglacParser::PragmaStatementContext *ctx) {
	WGLSymbol *target = lookupIdentifier(ctx->id, true)->effectiveTarget();

	const std::string name = WGLUtils::identifier(ctx->id->id.back());

	WGA_Symbol::PragmaValue value;
	if(auto v = ctx->valId)
		value = WGLUtils::identifier(v);

	else if(!ctx->valLit)
		value = true;

	else if(auto v = ctx->valLit->bool_)
		value = WGLUtils::identifier(v) == "true";

	else if(auto v = ctx->valLit->num)
		value = WGLUtils::numericLiteral(v);

	else throw;

	if(!target->parent() && name == "biomeGridSize") {
		ctx_->addApiCmd(nullptr, {}, [value](WGLAPIContext &ctx) {
			ctx.api->setBiomeGridSize(std::get<float>(value));
		});
	}
	else {
		static const std::unordered_set<int> supportedSymbolTypes{
			+WGLSymbol::Type::RuleExpansion,
			+WGLSymbol::Type::Rule,
			+WGLSymbol::Type::Component,
			+WGLSymbol::Type::ComponentNode
		};
		if(!supportedSymbolTypes.contains(+target->symbolType()))
			throw WGLError::WGLError("Pragmas are not supported for the given context.", ctx);

		ctx_->addApiCmd(nullptr, {target}, [target, name, value](WGLAPIContext &ctx) {
			ctx.map<WGA_Symbol>(target)->setPragma(name, value);
		});
	}
}

WGLImplementationPass::ExpressionResult
WGLImplementationPass::expression(WoglacParser::ExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	return expression(ctx->e, deps);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::TernaryExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->base)
		return expression(e, deps);

	const ExpressionResult baseCond = expression(ctx->condition, deps);

	ExpressionResult cond = baseCond;

	if(cond.type != WGA_Value::ValueType::Bool)
		cond = functionCall("bool", {cond}, ctx->condition);

	return functionCall("select", {cond, ctx->thenBranch ? expression(ctx->thenBranch, deps) : baseCond, expression(ctx->elseBranch, deps)}, ctx);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::LogicalExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->a)
		return expression(e, deps);

	if(auto e = ctx->o)
		return expression(e, deps);

	throw;
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::AndExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->base)
		return expression(e, deps);

	return functionCall("logAnd", {expression(ctx->left, deps), expression(ctx->right, deps)}, ctx);
}

WGLImplementationPass::ExpressionResult
WGLImplementationPass::expression(WoglacParser::OrExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->base)
		return expression(e, deps);

	return functionCall("logOr", {expression(ctx->left, deps), expression(ctx->right, deps)}, ctx);
}

WGLImplementationPass::ExpressionResult
WGLImplementationPass::expression(WoglacParser::ComparisonExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	static const std::unordered_map<std::string, std::string> ops{
		{"==", "compEq"},
		{"!=", "compNeq"},
		{"<=", "compLeq"},
		{">=", "compGeq"},
		{"<",  "compLt"},
		{">",  "compGt"}
	};

	if(auto e = ctx->base)
		return expression(e, deps);

	return functionCall(ops.at(WGLUtils::identifier(ctx->op)), {expression(ctx->left, deps), expression(ctx->right, deps)}, ctx);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::AddExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->base)
		return expression(e, deps);

	return binaryOperation(WGLUtils::identifier(ctx->op), expression(ctx->left, deps), expression(ctx->right, deps), ctx);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::MultExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->base)
		return expression(e, deps);

	return binaryOperation(WGLUtils::identifier(ctx->op), expression(ctx->left, deps), expression(ctx->right, deps), ctx);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::UnaryExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	static const std::unordered_map<std::string, std::string> ops{
		{"-", "inverse"},
		{"!", "logNot"},
		{"+", {}}
	};

	if(auto e = ctx->base)
		return expression(e, deps);

	const std::string funcName = ops.at(WGLUtils::identifier(ctx->op));
	auto e = ctx->arg;

	if(!funcName.empty())
		return functionCall(funcName, {expression(e, deps)}, ctx);
	else
		return expression(e, deps);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::AtomicExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->funcCall)
		return expression(e, deps);

	if(auto e = ctx->lit)
		return expression(e, deps);

	if(auto e = ctx->par)
		return expression(e->e, deps);

	if(auto e = ctx->bio)
		return expression(e, deps);

	if(auto e = ctx->id)
		return expression(e, deps);

	throw;
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::FunctionCallExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	return functionCall(WGLUtils::identifier(ctx->id), iterator(ctx->args->args).mapx(expression(x, deps)).toList(), ctx);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::LiteralExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->block) {
		const std::string uid = e->getText();

		/*BlockType *block = game()->managers.blockType.getBlockTypeByUID(uid);
		if(!block)
			throw WoglacSemanticError(QStringLiteral("Unknown block uid '%1'").arg(uid), this, ctx);*/

		return EXPRESSION_RESULT(ValueType::Block, ctx.api->constBlock(uid));
	}

	if(auto e = ctx->num) {
		const float val = WGLUtils::numericLiteral(e);
		return EXPRESSION_RESULT(ValueType::Float, ctx.api->constFloat(val));
	}

	if(auto e = ctx->bool_) {
		const bool val = WGLUtils::identifier(e) == "true";
		return EXPRESSION_RESULT(ValueType::Bool, ctx.api->constBool(val));
	}

	if(auto e = ctx->string) {
		throw WGLError("String literals are not supoprted", ctx);
	}

	throw;
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::InlineFunctionCallExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(ctx->base)
		return expression(ctx->base, deps);

	std::vector<ExpressionResult> args{expression(ctx->arg1, deps)};
	for(const ExpressionResult &arg: iterator(ctx->args->args).mapx(
		expression(x, deps)))
		args.push_back(arg);

	return functionCall(WGLUtils::identifier(ctx->id), args, ctx);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::ExtendedIdentifierContext *ctx, WGLImplementationPass::DependencyList &deps) {
	WGLSymbol *sym = lookupIdentifier(ctx, false);
	deps.insert(sym);

	switch(sym->symbolType()) {

		case SymbolType::FieldVariable:
			return EXPRESSION_RESULT(sym->valueType, ctx.map<WGA_Value>(sym));

		case SymbolType::StructureVariable:
		case SymbolType::StructureParam: {
			WGLSymbol *symp = sym->parent()->effectiveTarget();
			WGLSymbol *scp = currentScope()->effectiveTarget();

			if(symp != scp)
				throw WGLError(std::format("Local variable '{}' cannot be used outside of the rule/structure scope '{}'", sym->fullName(), symp->fullName()), ctx);

			return EXPRESSION_RESULT(sym->valueType, ctx.map<WGA_Value>(sym));
		}

		case SymbolType::Rule:
			return EXPRESSION_RESULT(ValueType::Rule, ctx.api->constRule(ctx.map<WGA_Rule>(sym)));

		case SymbolType::ComponentNode:
			return EXPRESSION_RESULT(ValueType::ComponentNode, ctx.api->constComponentNode(ctx.map<WGA_ComponentNode>(sym)));

		default:
			throw WGLError(std::format("Symbol '{}' of type '{}' cannot be used as a value.", sym->fullName(), WGLUtils::getSymbolTypeName(sym->symbolType())), ctx);

	}
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::expression(WoglacParser::BiomeParamExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	const std::string method = WGLUtils::identifier(ctx->method);

	WGLSymbol *param = lookupIdentifier(ctx->param, false);
	if(param->symbolType() != SymbolType::BiomeParam)
		throw WGLError(std::format("Symbol '{}' is not a biome param.", param->fullName()), ctx->param);

	deps.insert(param);

	std::vector<WGLImplementationPass::ExpressionResult> args;
	args.push_back(EXPRESSION_RESULT(param->valueType, ctx.map<WGA_Value>(param)));

	for(auto e: ctx->params)
		args.push_back(expression(e, deps));

	return functionCall("biomeParam_" + WGLUtils::identifier(ctx->method), args, ctx);
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::positionExpression(WoglacParser::PositionExpressionContext *ctx, WGLImplementationPass::DependencyList &deps) {
	if(auto e = ctx->vec) {
		ExpressionResult val = expression(e, deps);
		if(val.type != ValueType::Float3)
			throw WGLError(std::format("Position expression must evaluate to Float3 (type {} provided).", WGA_Value::typeNames.at(val.type)), ctx);

		return val;
	}

	return functionCall("float3", {expression(ctx->x, deps), expression(ctx->y, deps), expression(ctx->z, deps)}, ctx);
}

void WGLImplementationPass::componentNodeCommonPart(WGLSymbol *sym, WoglacParser::ComponentNodeStatementCommonPartContext *ctx, WGLSymbol *component, DependencyList &deps, const std::function<void(WGLAPIContext &, WGA_ComponentNode::Config &)> &cfgFunc) {
	ASSERT(component->symbolType() == SymbolType::Component);

	const std::string group = ctx->group ? WGLUtils::identifier(ctx->group) : std::string{};

	WGLSymbol *rule = ctx->rule_ ? lookupIdentifier(ctx->rule_, false) : nullptr;
	if(rule && rule->symbolType() != SymbolType::Rule)
		throw WGLError("Node expansion target must be a rule.", ctx);

	static const auto oriStr = [](const WoglacParser::ComponentNodeOrientationExpressionContext *ctx) {
		return ctx ? WGLUtils::identifier(ctx->dir) + WGLUtils::identifier(ctx->sign) : std::string{};
	};

	std::vector<std::pair<std::string, WGA_Symbol::PragmaValue >> pragmaSets;

	if(ctx->prop && ctx->prop->notAdjacent)
		pragmaSets.push_back({"adjacent", false});

	if(ctx->prop && ctx->prop->horizontalEdge)
		pragmaSets.push_back({"horizontalEdge", true});

	if(ctx->prop && ctx->prop->verticalEdge)
		pragmaSets.push_back({"verticalEdge", true});

	const BlockOrientation orientation = ctx->prop ? BlockOrientation(oriStr(ctx->prop->ori), oriStr(ctx->prop->ori2)) : BlockOrientation();

	if(rule)
		deps.insert(rule);

	ctx_->addApiCmd(sym, deps, [=](WGLAPIContext &ctx) {
		WGA_ComponentNode::Config cfg;
		cfg.group = group;
		cfg.rule = rule ? ctx.map<WGA_Rule>(rule) : nullptr;
		cfg.orientation = orientation;

		cfgFunc(ctx, cfg);

		WGA_ComponentNode *node = ctx.api->newComponentNode();
		node->setConfig(cfg);

		for(const auto &ps: pragmaSets)
			node->setPragma(ps.first, ps.second);

		ctx.addSymbolMapping(sym, node);

		ctx.map<WGA_Component>(component)->addNode(node);
	});
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::functionCall(const std::string &functionName, const std::vector<WGLImplementationPass::ExpressionResult> &args, antlr4::ParserRuleContext *ctx) {
	const WorldGenAPI::Functions &fs = WorldGenAPI::functions();

	if(!fs.nameSet.contains(functionName))
		throw WGLError(std::format("Function '{}' does not exist.", functionName), ctx);

	const std::string prototype = WorldGenAPI::Function::composePrototype(functionName, iterator(args).mapx(x.type).toList());

	WorldGenAPI::FunctionID fid;
	if(const auto i = fs.prototypeMapping.find(prototype); i != fs.prototypeMapping.end())
		fid = i->second;
	else
		throw WGLError(std::format("Function '{}' does not have overload '{}'.\nAcceptable overloads:\n{}", functionName, prototype, iterator(fs.nameMapping.at(functionName)).mapx(fs.list[x].prototype).join("\n")), ctx);

	const std::string desc = ctx->getText();

	const WorldGenAPI::Function &f = fs.list[fid];
	return ExpressionResult{
		[fid, args, desc](WGLAPIContext &ctx) {
			auto r = ctx.api->function(fid, iterator(args).mapx(x.func(ctx)).toList());
			r->setDescription(desc);
			return r;
		},
		f.returnValue.type
	};
}

WGLImplementationPass::ExpressionResult WGLImplementationPass::binaryOperation(const std::string &op, const WGLImplementationPass::ExpressionResult &a, const WGLImplementationPass::ExpressionResult &b, antlr4::ParserRuleContext *ctx) {
	static const std::unordered_map<std::string, std::string> ops{
		{"+", "add"},
		{"-", "sub"},
		{"*", "mult"},
		{"/", "div"}
	};

	return functionCall(ops.at(op), {a, b}, ctx);
}
