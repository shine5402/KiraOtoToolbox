#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "toolBase/tooldialogadapter.h"

class QAbstractButton;
class QStackedWidget;

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
    bool isBatchMode() const;
    bool isSingleMode() const;
    void switchToBatchMode();
    void switchToSingleMode();

public slots:
    void toggleMode();
private slots:
    void otoFileLoaded();
    void accept() override;
    void reset();
    void resetOto();
    void resetOptions();
    void buttonBoxClicked(QAbstractButton *button);

    void refreshOptionWidgetEnableState();
private:
    Ui::ToolDialog *ui;
    void reAssignUIWidgets();
    ToolDialogAdapter* adapter;
    bool doWork(const OtoEntryList& srcList, const QString& srcFileName, const OptionContainer& options, QWidget* dialogParent);
    bool doWork(const QList<OtoEntryList>& srcLists, const QStringList srcFileNames, const OptionContainer& options, QWidget* dialogParent);
    constexpr static auto singleModePageIndex = 0;
    constexpr static auto batchModePageIndex = 1;
    void refreshStackedWidgetSize(QStackedWidget* stackedWidget);

    void switchModePrivate(int pageIndex);
    static bool saveOtoFileWithErrorInform(const OtoEntryList& entryList, int decimalAccuracy, const QString& fileName, const QString& usage, QWidget* dialogParent);
};

#endif // TOOLDIALOG_H
