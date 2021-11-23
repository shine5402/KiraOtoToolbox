#include "otofilereader.h"
#include <utility>
#include <QTextDecoder>

OtoFileReader::OtoFileReader(QString fileName, QTextCodec* textCodec, bool keepInvalid) : fileName_(std::move(fileName)), fileInfo_({fileName}), textCodec_(textCodec), keepInvalid_(keepInvalid)
{
    fileInfo_.setCaching(false);
}

OtoEntryList OtoFileReader::getEntryList() const
{
    if (cacheValid())
        return entryListCache_;

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
            entryListCache_.append(otoEntry);
        }
        lastModifiedOnRead_ = fileInfo_.lastModified();
        return entryListCache_;
    }

    refresh();
    return entryListCache_;
}

void OtoFileReader::setFileName(QString fileName)
{
    fileName_ = std::move(fileName);
    refresh();
}

void OtoFileReader::setTextCodec(QTextCodec* codec)
{
    textCodec_ = codec;
    refresh();
}

void OtoFileReader::setKeepInvalid(bool value)
{
    keepInvalid_ = value;
    refresh();
}

void OtoFileReader::refresh() const
{
    entryListCache_.clear();
    lastModifiedOnRead_ = QDateTime();
}

QString OtoFileReader::fileName() const
{
    return fileName_;
}

QTextCodec* OtoFileReader::textCodec() const
{
    return textCodec_;
}

bool OtoFileReader::keepInvalid() const
{
    return keepInvalid_;
}

bool OtoFileReader::cacheValid() const
{
    return lastModifiedOnRead_.isValid() && fileInfo_.exists() && (lastModifiedOnRead_ == fileInfo_.lastModified());
}

