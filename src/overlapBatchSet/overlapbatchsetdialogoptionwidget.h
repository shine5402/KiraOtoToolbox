#ifndef OVERLAPBATCHSETDIALOGOPTIONWIDGET_H
#define OVERLAPBATCHSETDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>
#include "toolBase/tooloptionwidget.h"
#include <QStringListModel>

namespace Ui {
    class OverlapBatchSetDialogOptionWidget;
}

class OverlapBatchSetOptions : public ToolOptions {
    Q_OBJECT
public:
    explicit OverlapBatchSetOptions(QObject* parent = nullptr) : ToolOptions(parent){};
    bool setOverlapStartWith = false;
    double overlapStartWith = 0.0;
    QStringList startWithPatternList{};
    bool startWithMatchStartAlias = false;
    bool makeOneThird = false;

};

class OverlapBatchSetDialogOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    explicit OverlapBatchSetDialogOptionWidget(QWidget *parent = nullptr);
    ~OverlapBatchSetDialogOptionWidget();

    ToolOptions* getOptions(QObject* parent = nullptr) const override;
    void setOptions(const ToolOptions* options) override;

private:
    Ui::OverlapBatchSetDialogOptionWidget *ui;
    void loadPreset();
    struct preset{
        QString name;
        QStringList content;
    };
    QVector<preset> presetList;
    const QStringList* workingStartList = &emptyStringList;
    const static QStringList emptyStringList;
    QStringList notPresetStartList;
    QStringListModel startListModel;

    void setWorkingStartList(const QStringList* list);
private slots:
    void switchPreset(int index);
    void clearWorkingStartList();
    void loadStartListFromFile();
    void switchToUsePreset();
    void getStartListFromUserInput();
};

#endif // OVERLAPBATCHSETDIALOGOPTIONWIDGET_H
