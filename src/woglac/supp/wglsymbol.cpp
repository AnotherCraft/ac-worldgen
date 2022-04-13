#include "wglsymbol.h"

#include <QSet>

#include "util/enumutils.h"

#include "wglerror.h"
#include "wglcontext.h"

using Type = WGLSymbol::Type;

WGLSymbol::WGLSymbol(WGLContext *context, WGLSymbol *parent, const QString &name, Type type, antlr4::ParserRuleContext *declarationAst_)
	: context_(*context), parent_(parent), name_(name), type_(type), declarationAst_(declarationAst_) {
	ASSERT(!context_.astSymbolMapping.contains(declarationAst_));

	fullName_ = name_;

	if(fullName_.isEmpty())
		fullName_ = !parent ? QStringLiteral("(root)") : QStringLiteral("(anonymous %1)").arg(
			WGLUtils::getSymbolTypeName(type));

	desc_ = fullName_;
	if(declarationAst_ && declarationAst_->start && declarationAst_->stop && declarationAst_->start->getTokenSource())
		desc_ += ": " + QString::fromStdString(declarationAst_->start->getTokenSource()->getInputStream()->getText(antlr4::misc::Interval(declarationAst_->start->getStartIndex(), declarationAst_->stop->getStopIndex()))).trimmed().replace('\n', ' ');

	ASSERT(!desc_.isEmpty());

	context_.allSymbols += this;

	if(declarationAst_)
		context_.astSymbolMapping[declarationAst_] = this;

	if(parent_) {
		parent_->children_ += this;

		if(!name_.isEmpty()) {
			auto &child = parent_->childrenByName_[name_];

			if(child)
				throw WGLError(QStringLiteral("Symbol '%1' redefinition.").arg(child->fullName()), declarationAst_);

			child = this;
		}

		if(!parent_->fullName().isEmpty())
			fullName_ = QStringLiteral("%1.%2").arg(parent_->fullName(), name_);
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

WGLSymbol *WGLSymbol::resolveIdentifier(const QString &id, antlr4::ParserRuleContext *ctx, bool throwError) {
	WGLSymbol *result = childrenByName_.value(id);

	if(!result && throwError)
		throw WGLError(QStringLiteral("Failed to resolve identifier '%1' in scope '%2'").arg(id, fullName()), ctx);

	return result;
}

WGLSymbol::~WGLSymbol() {

}
