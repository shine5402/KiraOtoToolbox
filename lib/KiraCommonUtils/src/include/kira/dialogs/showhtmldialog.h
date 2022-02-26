#ifndef SHOWHTMLDIALOG_H
#define SHOWHTMLDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class ShowHTMLDialog;
}

class ShowHTMLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowHTMLDialog(QWidget *parent = nullptr);
    ~ShowHTMLDialog();

    void setTitle(const QString& title);
    void setLabel(const QString& text);
    void setHTML(const QString& html);
    void setMarkdown(const QString& markdown);
    void setStandardButtons(QDialogButtonBox::StandardButtons buttons);
private:
    Ui::ShowHTMLDialog *ui;
};

#endif // SHOWHTMLDIALOG_H
