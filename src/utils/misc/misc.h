#ifndef MISC_H
#define MISC_H

#include <QWidget>
#include <QLayout>
#include <QtCore/QtCore>
#include <otoentry.h>
#include <QDialogButtonBox>

namespace Misc {
    void replaceWidget(QLayout* parentLayout, const QString& widgetName,
                       QWidget* newWidget, QWidget* newParent = nullptr);

    enum ChangeAskDialogType{
        Determine, ValueChangeModel, Diff
    };
    bool showOtoDiffDialog(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, int precision,
                           const QString& title = {}, const QString& label = {}, QWidget* dialogParent = nullptr,
                           ChangeAskDialogType changeType = Determine,
                           QDialogButtonBox::StandardButtons stdButtons = QDialogButtonBox::Ok | QDialogButtonBox::Cancel
            );

    bool askUserWithShowOtoList(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent);

}

#endif // MISC_H
