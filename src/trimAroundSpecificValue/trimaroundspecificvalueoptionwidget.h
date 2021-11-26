#ifndef TRIMAROUNDSPECIFICVALUEOPTIONWIDGET_H
#define TRIMAROUNDSPECIFICVALUEOPTIONWIDGET_H

#include <QWidget>
#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class TrimAroundSpecificValueOptionWidget;
}

class TrimAroundSpecificValueOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit TrimAroundSpecificValueOptionWidget(QWidget *parent = nullptr);
    ~TrimAroundSpecificValueOptionWidget();

private:
    Ui::TrimAroundSpecificValueOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // TRIMAROUNDSPECIFICVALUEOPTIONWIDGET_H
