#ifndef OVERLAPBATCHSETDIALOGOPTIONWIDGET_H
#define OVERLAPBATCHSETDIALOGOPTIONWIDGET_H

#include <QWidget>
#include <otoentry.h>
#include "toolBase/tooloptionwidget.h"
#include <QStringListModel>

namespace Ui {
    class OverlapBatchSetDialogOptionWidget;
}

class OverlapBatchSetDialogOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    explicit OverlapBatchSetDialogOptionWidget(QWidget *parent = nullptr);
    ~OverlapBatchSetDialogOptionWidget();

    ToolOptions getOptions() const override;
    void setOptions(const ToolOptions& options) override;

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
