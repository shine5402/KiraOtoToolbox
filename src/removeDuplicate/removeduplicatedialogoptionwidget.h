#ifndef REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
#define REMOVEDUPLICATEDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>
#include "toolBase/tooloptionwidget.h"

namespace Ui {
    class RemoveDuplicateDialogOptionWidget;
}

class RemoveDuplicateDialogOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit RemoveDuplicateDialogOptionWidget(QWidget *parent = nullptr);
    ~RemoveDuplicateDialogOptionWidget();

    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
private:
    Ui::RemoveDuplicateDialogOptionWidget *ui;
};

#endif // REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
