#ifndef SETALIASOPTIONWIDGET_H
#define SETALIASOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class SetAliasOptionWidget;
}

class SetAliasOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit SetAliasOptionWidget(QWidget *parent = nullptr);
    ~SetAliasOptionWidget();

private:
    Ui::SetAliasOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;

    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // SETALIASOPTIONWIDGET_H
