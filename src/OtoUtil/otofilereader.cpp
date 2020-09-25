#include "otofilereader.h"
#include <utility>
#include <QTextDecoder>

OtoFileReader::OtoFileReader(QString fileName, QTextCodec* textCodec, bool keepInvalid) : m_fileName(std::move(fileName)), m_fileInfo({fileName}), m_textCodec(textCodec), m_keepInvalid(keepInvalid)
{
    m_fileInfo.setCaching(false);
}

OtoEntryList OtoFileReader::getEntryList() const
{
    if (cacheValid())
        return m_entryListCache;

    QFile file(fileName());
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        auto rawData = file.readAll();
        file.close();
        auto data = textCodec()->makeDecoder()->toUnicode(rawData);
        auto otoStringList = data.split("\n",Qt::SkipEmptyParts);
        for (const auto& otoString : otoStringList){
            auto otoEntry = OtoEntry(otoString);
            if ((!otoEntry.isValid()) && (!keepInvalid()))
                continue;
            m_entryListCache.append(otoEntry);
        }
        m_lastModifiedOnRead = m_fileInfo.lastModified();
        return m_entryListCache;
    }

    refresh();
    return m_entryListCache;
}

void OtoFileReader::setFileName(QString fileName)
{
    m_fileName = std::move(fileName);
    refresh();
}

void OtoFileReader::setTextCodec(QTextCodec* codec)
{
    m_textCodec = codec;
    refresh();
}

void OtoFileReader::setKeepInvalid(bool value)
{
    m_keepInvalid = value;
    refresh();
}

void OtoFileReader::refresh() const
{
    m_entryListCache.clear();
    m_lastModifiedOnRead = QDateTime();
}

QString OtoFileReader::fileName() const
{
    return m_fileName;
}

QTextCodec* OtoFileReader::textCodec() const
{
    return m_textCodec;
}

bool OtoFileReader::keepInvalid() const
{
    return m_keepInvalid;
}

bool OtoFileReader::cacheValid() const
{
    return m_lastModifiedOnRead.isValid() && m_fileInfo.exists() && (m_lastModifiedOnRead == m_fileInfo.lastModified());
}

