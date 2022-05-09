#pragma once

#include <vector>
#include <string>
#include <functional>

#include "pch.h"

// Woglac language parser and compiler, outputs a
class WGLCompiler {

public:
	using StreamFunction = std::function<std::unique_ptr<std::istream>(const std::string &filename)>;

public:
	WGLCompiler();

	void clear();

public:
	void addSourceFile(const std::string &file);

	/// Takes filename (either for source file or for vox file) and returns input stream for that file or throws std::exception.
	std::unique_ptr<std::istream> getFileStream(const std::string &filename, antlr4::ParserRuleContext *ctx);

	/// Sets the function used for creating a file stream for a given filename
	inline void setStreamFunction(const StreamFunction &function) {
		streamFunction_ = function;
	}

public:
	void compile();

public:
	// Calls appropriate WorldGenAPI functions to construct the worldgen pipeline, returns exports
	std::unordered_map<std::string, WGA_Value *> construct(WorldGenAPI &api);

private:
	std::vector<std::string> sourceFiles_;
	std::shared_ptr<WGLContext> context_;
	StreamFunction streamFunction_;

private:
	std::vector<std::shared_ptr<WGLModule>> modules_;

};

