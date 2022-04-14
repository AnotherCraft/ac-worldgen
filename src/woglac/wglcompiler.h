#pragma once

#include <QString>

#include "pch.h"

#include "wglfile.h"

// Woglac language parser and compiler, outputs a
class WGLCompiler {

public:
	WGLCompiler();

	void clear();

	inline void setLookupDirectories(const QStringList &set) {
		lookupDirectories_ = set;
	}

public:
	void addFile(const WGLFilePtr &file);

	// Tries to locate a specified file, throws if failed
	QString lookupFile(const QString &filename, antlr4::ParserRuleContext *ctx);

public:
	void compile();

public:
	// Calls appropriate WorldGenAPI functions to construct the worldgen pipeline, returns exports
	QHash<QString, WGA_Value*> construct(WorldGenAPI &api);

private:
	QList<WGLFilePtr> files_;
	std::shared_ptr<WGLContext> context_;
	QStringList lookupDirectories_;

private:
	QList<QSharedPointer<WGLModule>> modules_;

};

