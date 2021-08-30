#ifndef REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
#define REMOVEDUPLICATEDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>
#include "toolBase/tooloptionwidget.h"

namespace Ui {
    class RemoveDuplicateOptionWidget;
}

class RemoveDuplicateOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit RemoveDuplicateOptionWidget(QWidget *parent = nullptr);
    ~RemoveDuplicateOptionWidget();
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
private:
    Ui::RemoveDuplicateOptionWidget *ui;
};

#endif // REMOVEDUPLICATEDIALOGOPTIONWIDGET_H
