#ifndef OTOFILEREADER_H
#define OTOFILEREADER_H

#include <QObject>
#include "otoentry.h"
#include <QTextCodec>
#include <QList>
#include <QVector>
#include <QDateTime>
#include <QFileInfo>

class OtoFileReader
{
public:
    OtoFileReader(QString fileName, QTextCodec* textCodec = QTextCodec::codecForName("Shift-JIS"), bool keepInvalid = false);

    OtoEntryList read() const;

    void setFileName(QString fileName);
    void setTextCodec(QTextCodec* codec);
    void setKeepInvalid(bool value);
    QString fileName() const;
    QTextCodec* textCodec() const;
    bool keepInvalid() const;

private:
    QString fileName_{};
    QTextCodec* textCodec_;
    bool keepInvalid_;
};

#endif // OTOFILEREADER_H
