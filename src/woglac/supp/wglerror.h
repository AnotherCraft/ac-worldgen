#pragma once

// Must place before everything else because of antlr
#include "wglinclude.h"

#include <QString>

class WGLError {

public:
	WGLError(const QString &msg, antlr4::ParserRuleContext *ctx);

public:
	inline const QString &message() const {
		return message_;
	}

private:
	QString message_;

};

