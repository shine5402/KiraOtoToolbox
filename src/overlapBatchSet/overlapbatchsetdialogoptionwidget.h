#ifndef OVERLAPBATCHSETDIALOGOPTIONWIDGET_H
#define OVERLAPBATCHSETDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>
#include "toolBase/tooloptionwidget.h"
#include <QStringListModel>

namespace Ui {
    class OverlapBatchSetDialogOptionWidget;
}

class OverlapBatchSetDialogOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit OverlapBatchSetDialogOptionWidget(QWidget *parent = nullptr);
    ~OverlapBatchSetDialogOptionWidget();

    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;

private:
    Ui::OverlapBatchSetDialogOptionWidget *ui;
};

#endif // OVERLAPBATCHSETDIALOGOPTIONWIDGET_H
