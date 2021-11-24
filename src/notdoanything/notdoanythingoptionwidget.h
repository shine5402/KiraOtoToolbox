#ifndef NOTDOANYTHINGOPTIONWIDGET_H
#define NOTDOANYTHINGOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>
//TODO:migrate with emptyoptionwidget?
class NotDoAnythingOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NotDoAnythingOptionWidget(QWidget *parent = nullptr);

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;

    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // NOTDOANYTHINGOPTIONWIDGET_H
