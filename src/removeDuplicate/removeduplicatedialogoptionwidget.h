#ifndef REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
#define REMOVEDUPLICATEDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>
#include "toolBase/tooloptionwidget.h"

namespace Ui {
    class RemoveDuplicateDialogOptionWidget;
}

class RemoveDuplicateOptions : public ToolOptions {
    Q_OBJECT
public:
    explicit RemoveDuplicateOptions(QObject* parent = nullptr) : ToolOptions(parent){};
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
    explicit RemoveDuplicateDialogOptionWidget(QWidget *parent = nullptr);
    ~RemoveDuplicateDialogOptionWidget();
    ToolOptions* getOptions(QObject* parent = nullptr) const override;
    void setOptions(const ToolOptions* options) override;
private:
    Ui::RemoveDuplicateDialogOptionWidget *ui;
};

#endif // REMOVEDUPLICATEDIALOGOPTIONWIDGET_H