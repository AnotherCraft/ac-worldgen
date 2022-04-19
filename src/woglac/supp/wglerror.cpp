#include "wglerror.h"

#include <format>

WGLError::WGLError(const std::string &msg, antlr4::ParserRuleContext *ctx) {
	message_ = std::format("[{}] {}",
		ctx ? std::to_string(ctx->getStart()->getLine()) : std::string{},
		msg
	);
}
