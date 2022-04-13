#include "blockworldpos.h"

QString BlockWorldPos::toColonSeparatedString() const {
	return QStringLiteral("%1:%2:%3").arg(QString::number(x()), QString::number(y()), QString::number(z()));
}
