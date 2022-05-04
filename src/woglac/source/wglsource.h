#pragma once

#include <memory>
#include <iostream>

class WGLSource {

public:
	virtual ~WGLSource() {}

public:
	/// Returns an open stream for the source
	virtual std::unique_ptr<std::istream> openStream() const = 0;

	virtual std::string sourceName() const = 0;

};

using WGLSourcePtr = std::shared_ptr<WGLSource>;