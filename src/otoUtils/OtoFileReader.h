#ifndef OTOFILEREADER_H
#define OTOFILEREADER_H

#include <QDateTime>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QTextCodec>

#include "OtoEntry.h"

struct OtoReadError {
    int lineNumber = 0;
    QString content;
    OtoEntry::OtoEntryError error = OtoEntry::UnknownError;
};

class OtoFileReader
{
public:
    OtoFileReader(QString fileName, QTextCodec *textCodec = QTextCodec::codecForName("Shift-JIS"),
                  bool keepInvalid = false);

    OtoEntryList read();

    void setFileName(QString fileName);
    void setTextCodec(QTextCodec *codec);
    void setKeepInvalid(bool value);
    QString fileName() const;
    QTextCodec *textCodec() const;
    bool keepInvalid() const;

    QList<OtoReadError> readErrors() const;

private:
    QString fileName_{};
    QTextCodec *textCodec_;
    bool keepInvalid_;
    QList<OtoReadError> readErrors_;
};

#endif // OTOFILEREADER_H
