#pragma once

// Must place before everything else because of antlr
#include "wglinclude.h"

#include <QString>

class WGLError {

public:
	WGLError(const std::string &msg, antlr4::ParserRuleContext *ctx);

public:
	inline const std::string &message() const {
		return message_;
	}

private:
	std::string message_;

};

