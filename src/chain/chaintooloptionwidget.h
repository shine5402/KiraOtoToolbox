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
    ToolOptions getOptions() const override;
    void setOptions(const ToolOptions &options) override;

private:
    Ui::ChainToolOptionWidget *ui;
    ChainStepsModel* stepsModel;

    int getCurrentRow() const;
    void setCurrentRow(int row);

    void openStepSettings(int index);
    
private slots:
    void addStep();
    void removeCurrentStep();
    void moveUpCurrentStep();
    void moveDownCurrentStep();
    void openStepSettings();

};

#endif // CHAINTOOLOPTIONWIDGET_H
