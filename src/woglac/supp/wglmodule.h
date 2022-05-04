#pragma once

#include <memory>

#include "wglinclude.h"

class WGLModule {

public:
	std::unique_ptr<std::istream> stream;
	std::unique_ptr<antlr4::ANTLRInputStream> input;
	std::unique_ptr<WoglacLexer> lexer;
	std::unique_ptr<antlr4::CommonTokenStream> tokens;
	std::unique_ptr<WoglacParser> parser;
	WoglacParser::ModuleContext *ast;

};

