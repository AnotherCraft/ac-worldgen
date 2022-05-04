#pragma once

#include <memory>
#include <string>

#include "wglsource.h"

class WGLSourceFile : public WGLSource {

public:
	WGLSourceFile();
	WGLSourceFile(const std::string &fileName);

public:
	inline const std::string &fileName() const {
		return fileName_;
	}

	void setFileName(const std::string &fileName);

public:
	virtual std::unique_ptr<std::istream> openStream() const override;
	virtual std::string sourceName() const override;

private:
	std::string fileName_;

};
