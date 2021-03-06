#ifndef ADDAFFIXOPTIONWIDGET_H
#define ADDAFFIXOPTIONWIDGET_H

#include <QWidget>
#include <toolBase/tooloptionwidget.h>
#include <QLineEdit>

class AddAffixOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AddAffixOptionWidget(QWidget *parent = nullptr);
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
private:
    QLineEdit* prefixEdit;
    QLineEdit* suffixEdit;
};

#endif // ADDAFFIXOPTIONWIDGET_H
