#ifndef PRECENTEREDCHANGEVALUEOPTIONWIDGET_H
#define PRECENTEREDCHANGEVALUEOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class PreCenteredChangeValueOptionWidget;
}

class PreCenteredChangeValueOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit PreCenteredChangeValueOptionWidget(QWidget *parent = nullptr);
    ~PreCenteredChangeValueOptionWidget();

private:
    Ui::PreCenteredChangeValueOptionWidget *ui;
private slots:
    void setParamsWithUITempo();
    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // PRECENTEREDCHANGEVALUEOPTIONWIDGET_H
