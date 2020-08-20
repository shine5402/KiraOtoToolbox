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
    explicit RemoveAffixOptionWidget(QWidget *parent = nullptr);
    ~RemoveAffixOptionWidget();
    ToolOptions* getOptions(QObject *parent = nullptr) const override;
    void setOptions(const ToolOptions *options) override;

private:
    Ui::RemoveAffixOptionWidget *ui;
};

#endif // REMOVEAFFIXOPTIONWIDGET_H
