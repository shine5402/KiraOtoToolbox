#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "toolBase/tooldialogadapter.h"

//BUG: 提供给Adapter修改窗口标题的途径

namespace Ui {
    class ToolDialog;
}

class ToolDialog : public QDialog
{
    Q_OBJECT

#ifdef SHINE5402OTOBOX_TEST
    friend class RemoveDuplicateTest;
#endif

public:
    explicit ToolDialog(ToolDialogAdapter* adapter, QWidget *parent = nullptr);
    ~ToolDialog();

private slots:
    void otoFileLoaded();
    void accept() override;
private:
    Ui::ToolDialog *ui;
    void reAssignUIWidgets();
    ToolDialogAdapter* adapter;
};

#endif // TOOLDIALOG_H
