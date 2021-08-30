#ifndef SETALIASTOOLOPTIONWIDGET_H
#define SETALIASTOOLOPTIONWIDGET_H

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
};

#endif // SETALIASTOOLOPTIONWIDGET_H
