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

    OtoEntryList getEntryList() const;

    void setFileName(QString fileName);
    void setTextCodec(QTextCodec* codec);
    void setKeepInvalid(bool value);

    void refresh() const;

    QString fileName() const;
    QTextCodec* textCodec() const;
    bool keepInvalid() const;

private:
    QString fileName_{};
    QFileInfo fileInfo_;
    QTextCodec* textCodec_;
    bool keepInvalid_;
    mutable QDateTime lastModifiedOnRead_;
    mutable OtoEntryList entryListCache_;

    bool cacheValid() const;
};

#endif // OTOFILEREADER_H
