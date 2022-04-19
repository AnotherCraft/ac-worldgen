#include "wglfile.h"

WGLFile::WGLFile() {

}

WGLFile::WGLFile(const std::string &fileName) {
	setFileName(fileName);
}

void WGLFile::setFileName(const std::string &fileName) {
	if(fileName_ == fileName)
		return;

	fileName_ = fileName;
}
