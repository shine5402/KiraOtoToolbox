#ifndef REMOVESPECIFICENTRIESOPTIONWIDGET_H
#define REMOVESPECIFICENTRIESOPTIONWIDGET_H

#include <QWidget>
#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class RemoveSpecificEntriesOptionWidget;
}

class RemoveSpecificEntriesOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit RemoveSpecificEntriesOptionWidget(QWidget *parent = nullptr);
    ~RemoveSpecificEntriesOptionWidget();

    enum MatchStrategy{
        Exact = 0, Partial, Regex
    };

private:
    Ui::RemoveSpecificEntriesOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // REMOVESPECIFICENTRIESOPTIONWIDGET_H
