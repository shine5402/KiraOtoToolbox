#ifndef SHOWHTMLDIALOG_H
#define SHOWHTMLDIALOG_H

#include <QDialog>

namespace Ui {
class ShowHTMLDialog;
}

class ShowHTMLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowHTMLDialog(QWidget *parent = nullptr);
    ShowHTMLDialog(const QString &html,const QString &title,QWidget *parent = nullptr);
    ~ShowHTMLDialog();

    void setHTML(const QString &html);
private:
    Ui::ShowHTMLDialog *ui;
};

#endif // SHOWHTMLDIALOG_H
