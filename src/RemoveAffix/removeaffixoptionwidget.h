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
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;

    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;

private:
    Ui::RemoveAffixOptionWidget *ui;
};

#endif // REMOVEAFFIXOPTIONWIDGET_H
