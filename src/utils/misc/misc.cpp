#include "misc.h"
#include <QDialog>
#include <kira/dialogs/showdiffdialog.h>
#include <utils/models/otolistshowvaluechangemodel.h>
#include <kira/dialogs/tableviewdialog.h>
#include <QTimer>
#include <utils/dialogs/showotolistdialog.h>
#include "utils/misc/misc.h"

bool Misc::showOtoDiffDialog(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, int precision,
                             const QString& title, const QString& label, QWidget* dialogParent,
                             Misc::ChangeAskDialogType changeType, QDialogButtonBox::StandardButtons stdButtons)
{
    auto dialog = [&]() -> QDialog* {

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
}();
    return dialog->exec();
}

bool Misc::askUserWithShowOtoList(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent)
{
    auto dialog = new ShowOtoListDialog(&secondSaveData, dialogParent);
    dialog->setLabel(label);
    dialog->setWindowTitle(title);
    dialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    return dialog->exec();
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
