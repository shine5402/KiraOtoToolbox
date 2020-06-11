#ifndef REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
#define REMOVEDUPLICATEDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>

namespace Ui {
    class RemoveDuplicateDialogOptionWidget;
}

class RemoveDuplicateDialogOptionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RemoveDuplicateDialogOptionWidget(QWidget *parent = nullptr);
    ~RemoveDuplicateDialogOptionWidget();

    struct OptionStruct{
        bool ignoreSpecificSuffix = false;
        QStringList suffixList{};
        bool ignorePitchSuffix = false;
        QString bottomPitch{"C1"};
        QString topPitch{"C7"};
        Qt::CaseSensitivity pitchCaseSensitive = Qt::CaseInsensitive;
        OtoEntryFunctions::CharacterCase pitchCase = OtoEntryFunctions::Upper;
        int maxDuplicateCount = 1;
        bool shouldOrganize = false;
        bool organizeStartFrom1 = false;//if false, starts from 2
        OtoEntryFunctions::CharacterCase pitchCaseOrganized = OtoEntryFunctions::Upper;
    };

    OptionStruct getOptions() const;
    void setOptions(const OptionStruct& options);
private:
    Ui::RemoveDuplicateDialogOptionWidget *ui;
};

#endif // REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
