#ifndef ADDSUFFIXDIALOG_H
#define ADDSUFFIXDIALOG_H

#include <QDialog>
#include <otoentry.h>

namespace Ui {
    class AddSuffixDialog;
}

class AddSuffixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSuffixDialog(QWidget *parent = nullptr);
    ~AddSuffixDialog();

    void accept() override;
private:
    Ui::AddSuffixDialog *ui;
    OtoEntryList entryList = {};
    bool entryList_readed = false;
    void openFilePathBrowse();
    void loadOtoFile();
    void showOtoListDialog();
    void saveFilePathBrowse();
};

#endif // ADDSUFFIXDIALOG_H
