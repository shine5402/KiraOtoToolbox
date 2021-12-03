#include "convertplusminusrightotolistmodifyworker.h"
#include <utils/misc/fplusAdapter.h>
#include <QDir>
#include <QFileInfo>
#include <utils/misc/kfr_adapt.h>
#include <QTextEncoder>
#include <QTextDecoder>
#include <memory>

ConvertPlusMinusRightOtoListModifyWorker::ConvertPlusMinusRightOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{
}


bool ConvertPlusMinusRightOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto fileName = options.getOption("load/fileName").toString();
    auto dir = QFileInfo{fileName}.dir();
    auto savePositive = options.getOption("savePositive").toBool();
    auto saveNegative = options.getOption("saveNegative").toBool();
    Q_ASSERT(saveNegative ^ savePositive);

    auto interpretBySystemEncoding = options.getOption("interpretBySystemEncoding").toBool();
    auto getFileNameInSystemEncoding = [](const QString& fileName)->QString{
        auto encoder = std::unique_ptr<QTextEncoder>(QTextCodec::codecForName("Shift-JIS")->makeEncoder());
        auto decoder = std::unique_ptr<QTextDecoder>(QTextCodec::codecForLocale()->makeDecoder());

        return decoder->toUnicode(encoder->fromUnicode(fileName));
    };

    resultOtoList = fplus::transform([=](OtoEntry entry) -> OtoEntry{
        auto fileName = interpretBySystemEncoding ? getFileNameInSystemEncoding(entry.fileName()) : entry.fileName();
        auto filePath = dir.filePath(fileName);
        if (!QFileInfo{filePath}.exists())
            throw FileNotFoundException(filePath);
        bool openSucess = false;
        auto reader = kfr::audio_reader_wav<float>(kfr::open_qt_file_for_reading(filePath, &openSucess));
        if (!openSucess || reader.format().type == kfr::audio_sample_type::unknown)
            throw FileCannotReadException(filePath);

        auto waveLength = reader.format().length / reader.format().samplerate * 1000;
        auto positiveRight = entry.right() > 0 ? entry.right() : waveLength - (entry.left() + std::abs(entry.right()));
        auto negativeRight = entry.right() < 0 ? entry.right() : -(waveLength - entry.right() - entry.left());
        if (positiveRight < 0)
            throw InvalidRightValue(entry, positiveRight);
        if (negativeRight > 0)
            throw InvalidRightValue(entry, negativeRight);

        if (savePositive)
            entry.setRight(positiveRight);
        if (saveNegative)
            entry.setRight(negativeRight);

        return entry;
    }, srcOtoList);
    return true;
}
