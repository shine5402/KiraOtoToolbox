#ifndef OTOFILEREADER_H
#define OTOFILEREADER_H

#include <QObject>
#include "otoentry.h"
#include <QTextCodec>
#include <QList>
#include <QDateTime>
#include <QFileInfo>

using OtoEntryList = QList<OtoEntry>;
class QKIRAUTAUUTILS_EXPORT OtoFileReader
{
public:
    OtoFileReader(QString m_fileName, QTextCodec* m_textCodec = QTextCodec::codecForName("Shift-JIS"), bool m_keepInvalid = false);

    OtoEntryList getEntryList() const;

    void setFileName(QString fileName);
    void setTextCodec(QTextCodec* codec);
    void setKeepInvalid(bool value);

    void refresh() const;

    QString fileName() const;
    QTextCodec* textCodec() const;
    bool keepInvalid() const;

private:
    QString m_fileName{};
    QFileInfo m_fileInfo;
    QTextCodec* m_textCodec;
    bool m_keepInvalid;
    mutable QDateTime m_lastModifiedOnRead;
    mutable OtoEntryList m_entryListCache;

    bool cacheValid() const;
};

#endif // OTOFILEREADER_H
