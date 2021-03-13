#include "misc.h"
#include <QDialog>
#include <utils/dialogs/showdiffdialog.h>
#include <utils/models/otolistshowvaluechangemodel.h>
#include <utils/dialogs/tableviewdialog.h>
#include <QTimer>
#include <utils/dialogs/showotolistdialog.h>
#include "utils/misc/misc.h"

void Misc::replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent)
{
    auto oldWidget = parentLayout->parentWidget()->findChild<QWidget*>(widgetName);
    if (oldWidget){
        newWidget->setParent(newParent ? newParent : parentLayout->parentWidget());
        auto previousWidget = parentLayout->replaceWidget(oldWidget, newWidget);
        if (previousWidget){
            oldWidget->deleteLater();
            delete previousWidget;
        }
    }
}

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
#ifdef SHINE5402OTOBOX_TEST
    QTimer::singleShot(0, dialog, &QDialog::accept);
#endif
    return dialog->exec();
}

bool Misc::askUserWithShowOtoList(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent)
{
    auto dialog = new ShowOtoListDialog(&secondSaveData, dialogParent);
    dialog->setLabel(label);
    dialog->setWindowTitle(title);
    dialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
#ifdef SHINE5402OTOBOX_TEST
    QTimer::singleShot(0, dialog, &QDialog::accept);
#endif
    return dialog->exec();
}
