#ifndef SETALIASTOOLOPTIONWIDGET_H
#define SETALIASTOOLOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class SetAliasToolOptionWidget;
}

class SetAliasToolOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit SetAliasToolOptionWidget(QWidget *parent = nullptr);
    ~SetAliasToolOptionWidget();

private:
    Ui::SetAliasToolOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
};

#endif // SETALIASTOOLOPTIONWIDGET_H
