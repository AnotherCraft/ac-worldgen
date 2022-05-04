#pragma once

#include "wglsource.h"

class WGLSourceBuffer : public WGLSource {

public:
	WGLSourceBuffer(const std::string &data);

public:
	virtual std::unique_ptr<std::istream> openStream() const override;
	virtual std::string sourceName() const override;

private:
	const std::string data_;

};

