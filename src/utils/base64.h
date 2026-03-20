#ifndef KIRA_BASE64_H
#define KIRA_BASE64_H

#include <QString>
#include <QByteArray>

template <typename T>
    QString encodeBase64(const T& value){
        return QString::fromUtf8(QByteArray::fromRawData((const char*)&value, sizeof (T)).toBase64());
    }

    template <typename T>
    T decodeBase64(const QString& base64){
        if (base64.isEmpty())
            return {};
        return *((const T*) QByteArray::fromBase64(base64.toUtf8()).data());
    }

#endif