#pragma once

#include <vector>
#include <string>
#include <functional>

#include "pch.h"

// Woglac language parser and compiler, outputs a
class WGLCompiler {
public:
	WGLCompiler();

	void clear();

	inline void setLookupDirectories(const std::vector<std::string> &set) {
		lookupDirectories_ = set;
	}

public:
	void addFile(const std::string &file);

	// Tries to locate a specified file, throws if failed
	std::string lookupFile(const std::string &filename, antlr4::ParserRuleContext *ctx);

	std::unique_ptr<std::istream> getFileStream(const std::string &filename, antlr4::ParserRuleContext *ctx);

	inline void setStreamFunction(const std::function<std::unique_ptr<std::istream>(const std::string &filename, antlr4::ParserRuleContext *ctx)>& function) { openSteamFunction_ = function; }
public:
	void compile();

public:
	// Calls appropriate WorldGenAPI functions to construct the worldgen pipeline, returns exports
	std::unordered_map<std::string, WGA_Value*> construct(WorldGenAPI &api);

private:
	std::vector<std::string> files_;
	std::shared_ptr<WGLContext> context_;
	std::vector<std::string> lookupDirectories_;
	std::function<std::unique_ptr<std::istream>(const std::string &filename, antlr4::ParserRuleContext *ctx)> openSteamFunction_;

private:
	std::vector<std::shared_ptr<WGLModule>> modules_;

};

