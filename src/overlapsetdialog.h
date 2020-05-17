#ifndef OVERLAPSETDIALOG_H
#define OVERLAPSETDIALOG_H

#include <QDialog>
#include <otoentry.h>

namespace Ui {
    class OverlapSetDialog;
}

class OverlapSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OverlapSetDialog(QWidget *parent = nullptr);
    ~OverlapSetDialog();

private:
    Ui::OverlapSetDialog *ui;
    OtoEntryList entryList = {};
    bool entryList_readed = false;
    void loadPreset();
    struct preset{
        QString name;
        QStringList content;
    };
    QVector<preset> presetList;

private slots:
    void openFilePathBrowse();
    void loadOtoFile();
    void showOtoListDialog();

};

#endif // OVERLAPSETDIALOG_H
