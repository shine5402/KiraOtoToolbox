#ifndef MERGEOTOOPTIONWIDGET_H
#define MERGEOTOOPTIONWIDGET_H

#include <QWidget>
#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class MergeOtoOptionWidget;
}

class MergeOtoOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit MergeOtoOptionWidget(QWidget *parent = nullptr);
    ~MergeOtoOptionWidget();

    enum MergeStrategy{
        Replace = 0, Skip, KeepAll
    };

private:
    Ui::MergeOtoOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // MERGEOTOOPTIONWIDGET_H
