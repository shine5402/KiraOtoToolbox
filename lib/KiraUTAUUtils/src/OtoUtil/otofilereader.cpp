#include "otofilereader.h"
#include <utility>
#include <QTextDecoder>

OtoFileReader::OtoFileReader(QString fileName, QTextCodec* textCodec, bool keepInvalid) : fileName_(std::move(fileName)), textCodec_(textCodec), keepInvalid_(keepInvalid)
{
}

OtoEntryList OtoFileReader::read() const
{
    OtoEntryList result;
    QFile file(fileName());
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        auto rawData = file.readAll();
        file.close();
        auto data = textCodec()->makeDecoder()->toUnicode(rawData);
        auto otoStringList = data.split("\n",Qt::SkipEmptyParts);
        for (const auto& otoString : otoStringList){
            bool ok = false;
            auto otoEntry = OtoEntry::fromString(otoString, &ok, nullptr);
            if ((!ok) && (!keepInvalid()))
                continue;
            result.append(otoEntry);
        }
        return result;
    }
    return {};
}

void OtoFileReader::setFileName(QString fileName)
{
    fileName_ = std::move(fileName);
}

void OtoFileReader::setTextCodec(QTextCodec* codec)
{
    textCodec_ = codec;
}

void OtoFileReader::setKeepInvalid(bool value)
{
    keepInvalid_ = value;
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

