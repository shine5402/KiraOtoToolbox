#ifndef COPYORREPLACEBYALIASRULESMULTILINEEDITORDIALOG_H
#define COPYORREPLACEBYALIASRULESMULTILINEEDITORDIALOG_H
#include "copyorreplacebyaliasrule.h"

#include <QDialog>

namespace Ui {
    class CopyOrReplaceByAliasRulesMultiLineEditorDialog;
}

class CopyOrReplaceByAliasRulesMultiLineEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CopyOrReplaceByAliasRulesMultiLineEditorDialog(QWidget *parent = nullptr);
    ~CopyOrReplaceByAliasRulesMultiLineEditorDialog();

    QVector<CopyOrReplaceByAliasRule> rules() const;
    void setRules(QVector<CopyOrReplaceByAliasRule> rules);

    bool isValid() const;

private:
    Ui::CopyOrReplaceByAliasRulesMultiLineEditorDialog *ui;

    // QDialog interface
public slots:
    void accept() override;
};

#endif // COPYORREPLACEBYALIASRULESMULTILINEEDITORDIALOG_H
