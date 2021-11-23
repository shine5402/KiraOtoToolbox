#ifndef CHAININVALIDDIALOGADAPTER_H
#define CHAININVALIDDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>
#include <toolBase/tooloptionwidget.h>

class ChainInvalidDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE ChainInvalidDialogAdapter(QObject* parent = nullptr);
    QString getToolName() const override;
};

class QLabel;

class ChainInvalidOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE ChainInvalidOptionWidget(QWidget* parent = nullptr);

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
private:
    QString originalClassName;
    QLabel* label;
    QJsonObject originalOptionsJson;
};

#endif // CHAININVALIDDIALOGADAPTER_H
