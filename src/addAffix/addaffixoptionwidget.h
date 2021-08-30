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

    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;

private:
    QLineEdit* prefixEdit;
    QLineEdit* suffixEdit;
};

#endif // ADDAFFIXOPTIONWIDGET_H
