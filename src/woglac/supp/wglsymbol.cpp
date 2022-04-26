#include "wglsymbol.h"

#include <regex>

#include "util/enumutils.h"

#include "wglerror.h"
#include "wglcontext.h"

using Type = WGLSymbol::Type;

WGLSymbol::WGLSymbol(WGLContext *context, WGLSymbol *parent, const std::string &name, Type type, antlr4::ParserRuleContext *declarationAst_)
	: context_(*context), parent_(parent), name_(name), type_(type), declarationAst_(declarationAst_) {
	ASSERT(!context_.astSymbolMapping.contains(declarationAst_));

	fullName_ = name_;

	if(fullName_.empty())
		fullName_ = std::format("(anonymous {})", WGLUtils::getSymbolTypeName(type));

	desc_ = fullName_;
	if(declarationAst_ && declarationAst_->start && declarationAst_->stop && declarationAst_->start->getTokenSource()) {
		static const std::regex rx1("^\\s+|\\s+$"), rx2("\n");
		std::string str = declarationAst_->start->getTokenSource()->getInputStream()->getText(antlr4::misc::Interval(declarationAst_->start->getStartIndex(), declarationAst_->stop->getStopIndex()));
		str = std::regex_replace(str, rx1, "");
		str = std::regex_replace(str, rx2, " ");
		desc_.append(": " + str);
	}

	ASSERT(!desc_.empty());

	context_.allSymbols.push_back(this);

	if(declarationAst_)
		context_.astSymbolMapping[declarationAst_] = this;

	if(parent_) {
		parent_->children_.push_back(this);

		if(!name_.empty()) {
			auto &child = parent_->childrenByName_[name_];

			if(child)
				throw WGLError(std::format("Symbol '{}' redefinition.", child->fullName()), declarationAst_);

			child = this;
		}

		if(!parent_->fullName().empty())
			fullName_ = std::format("{}.{}", parent_->fullName(), name_);
	}

	effectiveTarget_ = this;
	while(effectiveTarget_->symbolType() == Type::Scope)
		effectiveTarget_ = effectiveTarget_->parent();
}

WGLSymbol *WGLSymbol::resolveIdentifier(const antlr4::Token *id, antlr4::ParserRuleContext *ctx, bool throwError) {
	if(!id)
		return this;

	return resolveIdentifier(WGLUtils::identifier(id), ctx, throwError);
}

WGLSymbol *WGLSymbol::resolveIdentifier(const std::string &id, antlr4::ParserRuleContext *ctx, bool throwError) {
	if(const auto f = childrenByName_.find(id); f != childrenByName_.end())
		return f->second;

	if(throwError)
		throw WGLError(std::format("Failed to resolve identifier '{}' in scope '{}'", id, fullName()), ctx);

	return nullptr;
}

WGLSymbol::~WGLSymbol() {

}
