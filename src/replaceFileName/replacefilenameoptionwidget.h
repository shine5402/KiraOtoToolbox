#ifndef REPLACEFILENAMEOPTIONWIDGET_H
#define REPLACEFILENAMEOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class ReplaceFileNameOptionWidget;
}

class ReplaceFileNameOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ReplaceFileNameOptionWidget(QWidget *parent = nullptr);
    ~ReplaceFileNameOptionWidget();

private:
    Ui::ReplaceFileNameOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // REPLACEFILENAMEOPTIONWIDGET_H
