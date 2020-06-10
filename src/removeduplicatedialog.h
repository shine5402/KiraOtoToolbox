#ifndef REMOVEDUPLICATEDIALOG_H
#define REMOVEDUPLICATEDIALOG_H

#include <QDialog>
#include <otoentry.h>

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
    explicit RemoveDuplicateDialog(QWidget *parent = nullptr);
    ~RemoveDuplicateDialog();

private slots:
    void addSuffix();
    void deleteSuffix();
    void modifySuffix();

    void otoFileLoaded();

    void accept() override;

private:
    Ui::RemoveDuplicateDialog *ui;
};

#endif // REMOVEDUPLICATEDIALOG_H
