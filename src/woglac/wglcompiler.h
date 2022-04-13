#pragma once

#include <QString>

#include "wglfile.h"

class WGLContext;
class WGLModule;

// Woglac language parser and compiler, outputs a
class WGLCompiler : public QObject {
Q_OBJECT

public:
	WGLCompiler();

	void clear();

public:
	void addFile(const WGLFilePtr &file);

public:
	void compile();

private:
	QList<WGLFilePtr> files_;
	std::shared_ptr<WGLContext> context_;

private:
	QList<QSharedPointer<WGLModule>> modules_;

};

