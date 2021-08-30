#ifndef CHAINTOOLOPTIONWIDGET_H
#define CHAINTOOLOPTIONWIDGET_H

#include <QWidget>
#include "toolBase/toolmanager.h"
#include "toolBase/tooloptionwidget.h"

class ChainStepsModel;

namespace Ui {
    class ChainToolOptionWidget;
}

class ChainToolOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ChainToolOptionWidget(QWidget *parent = nullptr);
    ~ChainToolOptionWidget();

    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer &options) override;

    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;

private:
    Ui::ChainToolOptionWidget *ui;
    ChainStepsModel* stepsModel;

    int getCurrentRow() const;
    void setCurrentRow(int row);

    void openStepSettings(int index);
    struct stepSettingsDialogInfo{
        stepSettingsDialogInfo() : ptrDialog(nullptr), ptrOptionWidget(nullptr), index(-1){};
        QDialog* ptrDialog;
        ToolOptionWidget* ptrOptionWidget;
        int index;
    } pendingStepSetting;
    
private slots:
    void addStep();
    void removeCurrentStep();
    void moveUpCurrentStep();
    void moveDownCurrentStep();
    void openStepSettings();
    void handleStepSettingsDone(int result);

};

#endif // CHAINTOOLOPTIONWIDGET_H
