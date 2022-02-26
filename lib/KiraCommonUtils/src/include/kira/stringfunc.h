#ifndef KIRA_STRINGFUNC_H
#define KIRA_STRINGFUNC_H

#include <QString>

QString removeSuffix(QString string, const QString& suffix, Qt::CaseSensitivity cs = Qt::CaseSensitive, bool* removed = nullptr);
QString removePrefix(QString string, const QString& prefix, Qt::CaseSensitivity cs = Qt::CaseSensitive, bool* removed = nullptr);
QString getDigitSuffix(const QString& string, int* position = nullptr, bool considerNegative = false);
QString removeDigitSuffix(QString string, int* position = nullptr, bool considerNegative = false, bool* removed = nullptr);

#endif