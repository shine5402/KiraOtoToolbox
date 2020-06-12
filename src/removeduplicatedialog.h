#ifndef REMOVEDUPLICATEDIALOG_H
#define REMOVEDUPLICATEDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "optionWidgets/removeduplicatedialogoptionwidget.h"
#include "widgets/otofilesavewidget.h"

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
    void otoFileLoaded();

    void accept() override;
private:
    Ui::RemoveDuplicateDialog *ui;
    void setupSpecificUIWidgets(QLayout* rootLayout);
    RemoveDuplicateDialogOptionWidget* optionWidget = new RemoveDuplicateDialogOptionWidget(this);
    OtoFileSaveWidgetWithSecondFileNameAsDeleted* saveWidget = new OtoFileSaveWidgetWithSecondFileNameAsDeleted(this);
};

#endif // REMOVEDUPLICATEDIALOG_H
