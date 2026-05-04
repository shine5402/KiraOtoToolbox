#ifndef OTOFILEREADER_H
#define OTOFILEREADER_H

#include <QDateTime>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QTextCodec>
#include <QVector>

#include "OtoEntry.h"

class OtoFileReader
{
public:
    OtoFileReader(QString fileName, QTextCodec *textCodec = QTextCodec::codecForName("Shift-JIS"),
                  bool keepInvalid = false);

    OtoEntryList read() const;

    void setFileName(QString fileName);
    void setTextCodec(QTextCodec *codec);
    void setKeepInvalid(bool value);
    QString fileName() const;
    QTextCodec *textCodec() const;
    bool keepInvalid() const;

private:
    QString fileName_{};
    QTextCodec *textCodec_;
    bool keepInvalid_;
};

#endif // OTOFILEREADER_H
