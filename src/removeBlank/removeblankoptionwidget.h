#ifndef REMOVEBLANKOPTIONWIDGET_H
#define REMOVEBLANKOPTIONWIDGET_H

#include "toolBase/tooloptionwidget.h"

class QCheckBox;

class RemoveBlankOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveBlankOptionWidget(QWidget* parent = nullptr);

    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer &options) override;

    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
private:
    QCheckBox* ignoreRightCheckBox = nullptr;
};

#endif // REMOVEBLANKOPTIONWIDGET_H
