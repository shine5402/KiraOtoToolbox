#ifndef REMOVEDUPLICATEDIALOG_H
#define REMOVEDUPLICATEDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "toolBase/tooldialogadapter.h"

namespace Ui {
    class RemoveDuplicateDialog;
}

class RemoveDuplicateDialog : public QDialog
{
    Q_OBJECT

#ifdef SHINE5402OTOBOX_TEST
    friend class RemoveDuplicateTest;
#endif

public:
    explicit RemoveDuplicateDialog(ToolDialogAdapter* adapter, QWidget *parent = nullptr);
    ~RemoveDuplicateDialog();

private slots:
    void otoFileLoaded();
    void accept() override;
private:
    Ui::RemoveDuplicateDialog *ui;
    void reAssignUIWidgets();
    ToolDialogAdapter* adapter;
};

#endif // REMOVEDUPLICATEDIALOG_H
