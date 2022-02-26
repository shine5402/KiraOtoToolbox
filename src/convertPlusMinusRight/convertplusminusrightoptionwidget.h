#ifndef CONVERTPLUSMINUSRIGHTOPTIONWIDGET_H
#define CONVERTPLUSMINUSRIGHTOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class ConvertPlusMinusRightOptionWidget;
}

class ConvertPlusMinusRightOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ConvertPlusMinusRightOptionWidget(QWidget *parent = nullptr);
    ~ConvertPlusMinusRightOptionWidget();

private:
    Ui::ConvertPlusMinusRightOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // CONVERTPLUSMINUSRIGHTOPTIONWIDGET_H
