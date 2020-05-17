#ifndef OVERLAPSETDIALOG_H
#define OVERLAPSETDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include <QStringListModel>

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
    const QStringList* workingStartList = &emptyStringList;
    const static QStringList emptyStringList;
    QStringList notPresetStartList;
    QStringListModel startListModel;

    void setWorkingStartList(const QStringList* list);

    void accept() override;

private slots:
    void openFilePathBrowse();
    void loadOtoFile();
    void showOtoListDialog();
    void switchPreset(int index);
    void clearWorkingStartList();
    void loadStartListFromFile();
    void switchToUsePreset();
    void getStartListFromUserInput();
    void saveFilePathBrowse();

};

#endif // OVERLAPSETDIALOG_H
