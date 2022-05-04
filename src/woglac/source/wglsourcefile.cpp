#include "wglsourcefile.h"

#include <fstream>
#include <format>

#include "woglac/supp/wglerror.h"

WGLSourceFile::WGLSourceFile() {

}

WGLSourceFile::WGLSourceFile(const std::string &fileName) {
	setFileName(fileName);
}

void WGLSourceFile::setFileName(const std::string &fileName) {
	if(fileName_ == fileName)
		return;

	fileName_ = fileName;
}

std::unique_ptr<std::istream> WGLSourceFile::openStream() const {
	auto r = std::make_unique<std::ifstream>();
	r->open(fileName_, std::ifstream::in);
	if(!r->is_open())
		throw WGLError(std::format("Error opening file '{}'", fileName_), nullptr);

	return r;
}

std::string WGLSourceFile::sourceName() const {
	return fileName_;
}
