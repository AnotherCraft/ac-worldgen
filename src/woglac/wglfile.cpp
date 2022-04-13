#include "wglfile.h"

WGLFile::WGLFile() {

}

WGLFile::WGLFile(const QString &fileName) {
	setFileName(fileName);
}

void WGLFile::setFileName(const QString &fileName) {
	if(fileName_ == fileName)
		return;

	fileName_ = fileName;
}
