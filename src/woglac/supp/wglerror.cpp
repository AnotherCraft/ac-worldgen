#include "wglerror.h"

WGLError::WGLError(const QString &msg, antlr4::ParserRuleContext *ctx) {
	message_ = QStringLiteral("[%1] %2").arg(
		ctx ? QString::number(ctx->getStart()->getLine()) : QString(),
		msg
	);
}
