#include "tracyutils.h"

#include <QReadWriteLock>
#include <QSharedPointer>
#include <QHash>

const char *TracyUtils::mapName(const QString &name) {
	static QReadWriteLock mx;
	static QHash<QString, char *> hash;

	char *result;

	{
		QReadLocker _ml(&mx);
		result = hash.value(name);
	}

	if(result)
		return result;

	const auto stdname = name.toStdString();
	result = new char[stdname.length() + 1];
	memcpy(result, stdname.c_str(), stdname.length() + 1);

	{
		QWriteLocker _ml(&mx);
		if(hash.contains(name)) {
			delete result;
			result = hash[name];
		} else
			hash[name] = result;
	}

	return result;
}
