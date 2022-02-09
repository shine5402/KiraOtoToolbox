#include "convertplusminusrightotolistmodifyworker.h"
#include "utils/misc/misc.h"
#include <kira/lib_helper/fplus_qt_adapter.h>
#include <QDir>
#include <QFileInfo>
#include <kira/lib_helper/kfr_helper.h>
#include <QTextEncoder>
#include <QTextDecoder>
#include <memory>

ConvertPlusMinusRightOtoListModifyWorker::ConvertPlusMinusRightOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{
}


void ConvertPlusMinusRightOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto fileName = options.getOption("load/fileName").toString();
    auto dir = QFileInfo{fileName}.dir();
    auto savePositive = options.getOption("savePositive").toBool();
    auto saveNegative = options.getOption("saveNegative").toBool();
    Q_ASSERT(saveNegative ^ savePositive);

    auto interpretBySystemEncoding = options.getOption("interpretBySystemEncoding").toBool();

    resultOtoList = fplus::transform([=](OtoEntry entry) -> OtoEntry{
        auto fileName = interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(entry.fileName()) : entry.fileName();
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
}
