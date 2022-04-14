#pragma once

#include <QString>

#include "pch.h"

#include "wglfile.h"

// Woglac language parser and compiler, outputs a
class WGLCompiler {

public:
	WGLCompiler();

	void clear();

public:
	void addFile(const WGLFilePtr &file);

	// Tries to locate a specified file, throws if failed
	QString lookupFile(const QString &filename);

public:
	void compile();

public:
	struct ExportValue {
		QString name;
		WGA_Value *value;
	};

	// Calls appropriate WorldGenAPI functions to construct the worldgen pipeline, returns list of root 
	QList<ExportValue> construct(WorldGenAPI &api);

private:
	QList<WGLFilePtr> files_;
	std::shared_ptr<WGLContext> context_;

private:
	QList<QSharedPointer<WGLModule>> modules_;

};

