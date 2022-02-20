#include <kira/dialogs/showhtmldialog.h>
#include "ui_showhtmldialog.h"

ShowHTMLDialog::ShowHTMLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowHTMLDialog)
{
    ui->setupUi(this);
}

ShowHTMLDialog::~ShowHTMLDialog()
{
    delete ui;
}

void ShowHTMLDialog::setTitle(const QString& title)
{
    setWindowTitle(title);
}

void ShowHTMLDialog::setLabel(const QString& text)
{
    ui->label->setText(text);
}

void ShowHTMLDialog::setHTML(const QString &html)
{
    ui->textBrowser->setHtml(html);
    auto cursor = ui->textBrowser->textCursor();
    cursor.setPosition(0);
    ui->textBrowser->setTextCursor(cursor);
}

void ShowHTMLDialog::setMarkdown(const QString& markdown)
{
    ui->textBrowser->document()->setMarkdown(markdown);
    auto cursor = ui->textBrowser->textCursor();
    cursor.setPosition(0);
    ui->textBrowser->setTextCursor(cursor);
}

void ShowHTMLDialog::setStandardButtons(QDialogButtonBox::StandardButtons buttons)
{
    ui->buttonBox->setStandardButtons(buttons);
}
