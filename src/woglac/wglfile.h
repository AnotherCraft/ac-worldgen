#pragma once

#include <QString>
#include <QSharedPointer>

class WGLFile {

public:
	WGLFile();
	WGLFile(const QString &fileName);

public:
	inline const QString &fileName() const {
		return fileName_;
	}

	void setFileName(const QString &fileName);

private:
	QString fileName_;

};

using WGLFilePtr = QSharedPointer<WGLFile>;
