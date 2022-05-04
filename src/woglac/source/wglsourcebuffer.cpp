#include "wglsourcebuffer.h"

#include <sstream>

WGLSourceBuffer::WGLSourceBuffer(const std::string &data) : data_(data) {

}

std::unique_ptr<std::istream> WGLSourceBuffer::openStream() const {
	return std::make_unique<std::istringstream>(data_);
}

std::string WGLSourceBuffer::sourceName() const {
	return std::format("(buffer {})", reinterpret_cast<intptr_t>(data_.data()));
}
