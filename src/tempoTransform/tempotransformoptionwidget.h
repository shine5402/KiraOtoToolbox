#ifndef TEMPOTRANSFORMOPTIONWIDGET_H
#define TEMPOTRANSFORMOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class TempoTransformOptionWidget;
}

class TempoTransformOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit TempoTransformOptionWidget(QWidget *parent = nullptr);
    ~TempoTransformOptionWidget();

    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;

    void askOtoDataCallback(int askId, const QVector<OtoEntryList>& contents) override;

private:
    Ui::TempoTransformOptionWidget *ui;

    static constexpr auto guessTempoAskId = 0;
};

#endif // TEMPOTRANSFORMOPTIONWIDGET_H
