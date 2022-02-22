#include "misc.h"
#include <QDialog>
#include <kira/dialogs/showdiffdialog.h>
#include <utils/models/otolistshowvaluechangemodel.h>
#include <kira/dialogs/tableviewdialog.h>
#include <QTimer>
#include <utils/dialogs/showotolistdialog.h>
#include "utils/misc/misc.h"
//#undef UNICODE
#include <compact_enc_det/compact_enc_det.h>
#include <QMessageBox>

QDialog* Misc::getOtoDiffDialog(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, int precision,
                                        const QString& title, const QString& label, QWidget* dialogParent,
                                        ChangeAskDialogType changeType, QDialogButtonBox::StandardButtons stdButtons)
{
    if (changeType == Determine){
        changeType = srcOtoList.count() == resultOtoList.count() ? Misc::ValueChangeModel : Misc::Diff;
    }

    switch (changeType) {
        case (ValueChangeModel):{
            auto model = new OtoListShowValueChangeModel(&srcOtoList, &resultOtoList, precision, dialogParent);
            return new TableViewDialog(dialogParent, model, title, label, stdButtons);
        }
        case (Diff):{
            auto otoList2String = [](const OtoEntryList& list, int precision) -> QString{
                QStringList stringList{};
                for (const auto& i : list){
                    stringList.append(i.toString(precision));
                }
                return stringList.join("\n");
            };
            return new ShowDiffDialog(otoList2String(srcOtoList, precision), otoList2String(resultOtoList, precision), title, label, stdButtons, dialogParent);
        }
        case (Determine): Q_UNREACHABLE();
    }
    return nullptr;
}

bool Misc::showOtoDiffDialog(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, int precision,
                             const QString& title, const QString& label, QWidget* dialogParent,
                             Misc::ChangeAskDialogType changeType, QDialogButtonBox::StandardButtons stdButtons)
{
    return getOtoDiffDialog(srcOtoList, resultOtoList, precision, title, label, dialogParent, changeType, stdButtons)->exec();
}

bool Misc::askUserWithShowOtoList(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent)
{
    return getAskUserWithShowOtoListDialog(secondSaveData, title, label, dialogParent)->exec();
}

QJsonArray Misc::arrayFromJsonValueVector(QVector<QJsonValue> vector){
    QJsonArray array;
    for (const auto& i : qAsConst(vector))
    {
        array.append(i);
    }
    return array;
}

QString Misc::getFileNameInSystemEncoding(const QString& fileName)
{
    auto encoder = std::unique_ptr<QTextEncoder>(QTextCodec::codecForName("Shift-JIS")->makeEncoder());
    auto decoder = std::unique_ptr<QTextDecoder>(QTextCodec::codecForLocale()->makeDecoder());

    return decoder->toUnicode(encoder->fromUnicode(fileName));
}

QDialog* Misc::getAskUserWithShowOtoListDialog(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent)
{
    auto dialog = new ShowOtoListDialog(&secondSaveData, dialogParent);
    dialog->setLabel(label);
    dialog->setWindowTitle(title);
    dialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    return dialog;
}

/// @returns The actual codec to use when reading
QTextCodec* Misc::detectCodecAndAskUserIfNotShiftJIS(const QString& path, QWidget* dialogParent) {
    QFile file(path);
    if (file.open(QFile::Text | QFile::ReadOnly)){
        auto content = file.readAll().toStdString();
        int bytes_consumed;
        bool is_reliable;
        auto detectedEncoding = CompactEncDet::DetectEncoding(content.c_str(), content.size(),
                                      nullptr, nullptr, nullptr, Encoding::SOFTBANK_SHIFT_JIS, Language::JAPANESE, CompactEncDet::QUERY_CORPUS, true,
                                      &bytes_consumed, &is_reliable);
        if (detectedEncoding != SOFTBANK_SHIFT_JIS){
            auto msg = QCoreApplication::translate("Misc", "The text encoding of file \"%1\" seems like %2 instead of Shift-JIS.\n"
                                                           "Should we use this encoding to read this file?\n"
                                                           "(Shift-JIS will always be used when saving files.)")
                    .arg(path, MimeEncodingName(detectedEncoding));
            //As EUC-JP and GB are basiclly same on Japanese hiragana, detecting on those will always be "unreliable"
            //but use either of them while reading typically oto file will cause no issue at all
            //so we choose not to inform user about it here.
//            if (!is_reliable){
//                msg += QCoreApplication::translate("Misc", "\n(Detecting result seems unreliable, so check twice before answer this dialog.)");
//            }
            auto result = QMessageBox::question(dialogParent, {}, msg);
            if (result == QMessageBox::Yes)
                return QTextCodec::codecForName(MimeEncodingName(detectedEncoding));
        }
    }
    return QTextCodec::codecForName("Shift-JIS");
}
