#pragma once

#include <vector>
#include <string>

#include "pch.h"

#include "wglfile.h"

// Woglac language parser and compiler, outputs a
class WGLCompiler {

public:
	WGLCompiler();

	void clear();

	inline void setLookupDirectories(const std::vector<std::string> &set) {
		lookupDirectories_ = set;
	}

public:
	void addFile(const WGLFilePtr &file);

	// Tries to locate a specified file, throws if failed
	QString lookupFile(const std::string &filename, antlr4::ParserRuleContext *ctx);

public:
	void compile();

public:
	// Calls appropriate WorldGenAPI functions to construct the worldgen pipeline, returns exports
	std::unordered_map<std::string, WGA_Value*> construct(WorldGenAPI &api);

private:
	std::vector<WGLFilePtr> files_;
	std::shared_ptr<WGLContext> context_;
	std::vector<std::string> lookupDirectories_;

private:
	std::vector<std::shared_ptr<WGLModule>> modules_;

};

