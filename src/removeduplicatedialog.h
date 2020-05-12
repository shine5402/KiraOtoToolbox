#ifndef REMOVEDUPLICATEDIALOG_H
#define REMOVEDUPLICATEDIALOG_H

#include <QDialog>

namespace Ui {
    class RemoveDuplicateDialog;
}

class RemoveDuplicateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveDuplicateDialog(QWidget *parent = nullptr);
    ~RemoveDuplicateDialog();

private:
    Ui::RemoveDuplicateDialog *ui;
};

#endif // REMOVEDUPLICATEDIALOG_H
