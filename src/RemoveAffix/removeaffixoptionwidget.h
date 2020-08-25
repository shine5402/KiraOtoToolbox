#ifndef REMOVEAFFIXOPTIONWIDGET_H
#define REMOVEAFFIXOPTIONWIDGET_H

#include <QWidget>
#include "toolBase/tooloptionwidget.h"

namespace Ui {
    class RemoveAffixOptionWidget;
}

class RemoveAffixOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit RemoveAffixOptionWidget(QWidget *parent = nullptr);
    ~RemoveAffixOptionWidget();
    ToolOptions getOptions() const override;
    void setOptions(const ToolOptions& options) override;

private:
    Ui::RemoveAffixOptionWidget *ui;
};

#endif // REMOVEAFFIXOPTIONWIDGET_H
