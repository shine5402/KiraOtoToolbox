#include "OtoFileReader.h"

#include <QTextDecoder>
#include <utility>

OtoFileReader::OtoFileReader(QString fileName, QTextCodec *textCodec, bool keepInvalid)
    : fileName_(std::move(fileName)), textCodec_(textCodec), keepInvalid_(keepInvalid)
{
}

OtoEntryList OtoFileReader::read()
{
    OtoEntryList result;
    readErrors_.clear();
    QFile file(fileName());
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        auto rawData = file.readAll();
        file.close();
        auto data = textCodec()->makeDecoder()->toUnicode(rawData);
        auto otoStringList = data.split("\n", Qt::SkipEmptyParts);
        int lineNumber = 0;
        for (const auto &otoString : otoStringList) {
            lineNumber++;
            bool ok = false;
            OtoEntry::OtoEntryError error = OtoEntry::UnknownError;
            auto otoEntry = OtoEntry::fromString(otoString, &ok, &error);
            if ((!ok) && (!keepInvalid())) {
                readErrors_.append({lineNumber, otoString, error});
                continue;
            }
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

void OtoFileReader::setTextCodec(QTextCodec *codec)
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

QTextCodec *OtoFileReader::textCodec() const
{
    return textCodec_;
}

bool OtoFileReader::keepInvalid() const
{
    return keepInvalid_;
}

QList<OtoReadError> OtoFileReader::readErrors() const
{
    return readErrors_;
}
