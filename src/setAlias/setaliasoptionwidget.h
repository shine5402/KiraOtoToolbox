#ifndef SETALIASOPTIONWIDGET_H
#define SETALIASOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class SetAliasToolOptionWidget;
}

class SetAliasOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit SetAliasOptionWidget(QWidget *parent = nullptr);
    ~SetAliasOptionWidget();

private:
    Ui::SetAliasToolOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;

    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
};

#endif // SETALIASOPTIONWIDGET_H
