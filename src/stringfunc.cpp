#include <kira/stringfunc.h>

QString removeSuffix(QString string, const QString& suffix, Qt::CaseSensitivity cs, bool* removed)
{
    auto suffixPos = string.lastIndexOf(suffix, -1, cs);
    if (removed)
        *removed = suffixPos != -1;
    if (suffixPos != -1)
    {
        return string.remove(suffixPos, suffix.count());
    }
    return string;
}

QString removePrefix(QString string, const QString& prefix, Qt::CaseSensitivity cs, bool* removed)
{
    auto prefixPos = string.indexOf(prefix, 0, cs);
    if (removed)
        *removed = prefixPos != -1;
    if (prefixPos != -1)
    {
        return string.remove(prefixPos, prefix.count());
    }
    return string;
}

QString getDigitSuffix(const QString& string, int* position, bool considerNegative)
{
    QString result{};
    for (int current = string.count() - 1; current >= 0; --current)
    {
        if (auto c = string.at(current);c.isDigit()){
            result.prepend(c);
        }
        else
        {
            if (considerNegative && current >= 0 && string.at(current) == '-')
            {
                result.prepend(string.at(current));
                current -= 1;
            }
            if (position)
            {
                *position = (current != string.count() - 1) ? current + 1 : -1;
            }
            break;
        }
    }
    return result;
}

QString removeDigitSuffix(QString string, int* position, bool considerNegative, bool* removed)
{
    return removeSuffix(string, getDigitSuffix(string, position, considerNegative), Qt::CaseInsensitive, removed);
}
