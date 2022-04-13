#pragma once

#include "wglinclude.h"

#include <QScopedPointer>

class WGLModule {

public:
	QScopedPointer<std::ifstream> stream;
	QScopedPointer<antlr4::ANTLRInputStream> input;
	QScopedPointer<WoglacLexer> lexer;
	QScopedPointer<antlr4::CommonTokenStream> tokens;
	QScopedPointer<WoglacParser> parser;
	WoglacParser::ModuleContext *ast;

};

