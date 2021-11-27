#ifndef VOWELCROSSFADINGOPTIONWIDGET_H
#define VOWELCROSSFADINGOPTIONWIDGET_H

#include <QWidget>
#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class VowelCrossfadingOptionWidget;
}

class VowelCrossfadingOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit VowelCrossfadingOptionWidget(QWidget *parent = nullptr);
    ~VowelCrossfadingOptionWidget();

private:
    Ui::VowelCrossfadingOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // VOWELCROSSFADINGOPTIONWIDGET_H
