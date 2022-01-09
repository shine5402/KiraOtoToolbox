#include <kira/dialogs/showhtmldialog.h>
#include "ui_showhtmldialog.h"

ShowHTMLDialog::ShowHTMLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowHTMLDialog)
{
    ui->setupUi(this);
}

ShowHTMLDialog::ShowHTMLDialog(const QString &html, const QString &title, QWidget *parent) : ShowHTMLDialog(parent)
{
    setWindowTitle(title);
    setHTML(html);
}

ShowHTMLDialog::~ShowHTMLDialog()
{
    delete ui;
}

void ShowHTMLDialog::setHTML(const QString &html)
{
    ui->textBrowser->setHtml(html);
}
