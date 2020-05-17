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
    void openFilePathBrowse();
    void loadOtoFile();

    void showOtoListDialog();
    void addSuffix();
    void deleteSuffix();
    void modifySuffix();

    void saveFilePathBrowse();

    void saveDeletedFilePathBrowse();

    void accept() override;

private:
    Ui::RemoveDuplicateDialog *ui;
    OtoEntryList entryList = {};
    bool entryList_readed = false;
};

#endif // REMOVEDUPLICATEDIALOG_H
