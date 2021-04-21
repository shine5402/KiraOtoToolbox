#ifndef REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
#define REMOVEDUPLICATEDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>
#include "toolBase/tooloptionwidget.h"

namespace Ui {
    class RemoveDuplicateDialogOptionWidget;
}

class RemoveDuplicateOptions : public OptionContainer {
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemoveDuplicateOptions(QObject* parent = nullptr) : OptionContainer(parent){};
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

class RemoveDuplicateDialogOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit RemoveDuplicateDialogOptionWidget(QWidget *parent = nullptr);
    ~RemoveDuplicateDialogOptionWidget();
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
private:
    Ui::RemoveDuplicateDialogOptionWidget *ui;
};

#endif // REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
