#pragma once

#include <memory>
#include <string>

class WGLFile {

public:
	WGLFile();
	WGLFile(const std::string &fileName);

public:
	inline const std::string &fileName() const {
		return fileName_;
	}

	void setFileName(const std::string &fileName);

private:
	std::string fileName_;

};

using WGLFilePtr = std::shared_ptr<WGLFile>;
