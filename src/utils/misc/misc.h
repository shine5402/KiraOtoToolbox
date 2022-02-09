#ifndef MISC_H
#define MISC_H

#include <QWidget>
#include <QLayout>
#include <QtCore/QtCore>
#include <OtoUtil/otoentry.h>
#include <QDialogButtonBox>

namespace Misc {
    enum ChangeAskDialogType{
        Determine, ValueChangeModel, Diff
    };
    QDialog* getOtoDiffDialogInstance(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, int precision,
                                      const QString& title = {}, const QString& label = {}, QWidget* dialogParent = nullptr,
                                      ChangeAskDialogType changeType = Determine,
                                      QDialogButtonBox::StandardButtons stdButtons = QDialogButtonBox::Ok | QDialogButtonBox::Cancel
            );
    bool showOtoDiffDialog(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, int precision,
                           const QString& title = {}, const QString& label = {}, QWidget* dialogParent = nullptr,
                           ChangeAskDialogType changeType = Determine,
                           QDialogButtonBox::StandardButtons stdButtons = QDialogButtonBox::Ok | QDialogButtonBox::Cancel
            );

    bool askUserWithShowOtoList(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent);

    QJsonArray arrayFromJsonValueVector(QVector<QJsonValue> vector);

    QString getFileNameInSystemEncoding(const QString& fileName);
}

#endif // MISC_H
