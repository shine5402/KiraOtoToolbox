#ifndef REPLACERULESMULTILINEEDITORDIALOG_H
#define REPLACERULESMULTILINEEDITORDIALOG_H
#include "replacerule.h"

#include <QDialog>

namespace Ui {
    class ReplaceRulesMultiLineEditorDialog;
}

class ReplaceRulesMultiLineEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceRulesMultiLineEditorDialog(QWidget *parent = nullptr);
    ~ReplaceRulesMultiLineEditorDialog();

    QVector<ReplaceRule> rules() const;
    void setRules(QVector<ReplaceRule> rules);

    bool isValid() const;

private:
    Ui::ReplaceRulesMultiLineEditorDialog *ui;

    // QDialog interface
public slots:
    void accept() override;
};

#endif // REPLACERULESMULTILINEEDITORDIALOG_H
