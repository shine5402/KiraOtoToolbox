#include "MiscUtils.h"

#include <QTextCodec>

QJsonArray Misc::arrayFromJsonValueVector(QVector<QJsonValue> vector)
{
    QJsonArray array;
    for (const auto &i : qAsConst(vector)) {
        array.append(i);
    }
    return array;
}

QString Misc::getFileNameInSystemEncoding(const QString &fileName)
{
    auto encoder = std::unique_ptr<QTextEncoder>(QTextCodec::codecForName("Shift-JIS")->makeEncoder());
    auto decoder = std::unique_ptr<QTextDecoder>(QTextCodec::codecForLocale()->makeDecoder());

    return decoder->toUnicode(encoder->fromUnicode(fileName));
}
