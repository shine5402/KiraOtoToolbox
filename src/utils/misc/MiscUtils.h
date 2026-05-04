#ifndef MISCUTILS_H
#define MISCUTILS_H

#include <QJsonArray>
#include <QString>
#include <QVector>

namespace Misc {
QJsonArray arrayFromJsonValueVector(QVector<QJsonValue> vector);
QString getFileNameInSystemEncoding(const QString &fileName);
} // namespace Misc

#endif // MISCUTILS_H
