#include "assert.h"

#include <QDebug>

void assertError(const char *assert, const char *file, int line, const QString &msg) {
	qWarning().noquote() << QStringLiteral("\n\n\n!!! assert FAILURE (%1:%2): %3").arg(file, QString::number(line), !msg.isEmpty() ? msg : assert);
	throw AssertFailureException();
}
