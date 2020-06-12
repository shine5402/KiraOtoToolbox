#include "otofilesavewidget.h"
#include "ui_otofilesavewidget.h"

OtoFileSaveWidget::OtoFileSaveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtoFileSaveWidget)
{
    ui->setupUi(this);
    refreshSecondFileNameWidgetVisible();
}

OtoFileSaveWidget::~OtoFileSaveWidget()
{
    delete ui;
}

bool OtoFileSaveWidget::isSaveToSrc() const
{
    return ui->saveToSrcRadioButton->isChecked();
}

bool OtoFileSaveWidget::isSaveToCustom() const
{
    return ui->saveToCustomRadioButton->isChecked();
}

QString OtoFileSaveWidget::fileName() const
{
    return ui->saveFileNameEdit->fileName();
}

bool OtoFileSaveWidget::isSecondFileNameUsed() const
{
    Q_ASSERT(ui->secondFileNameCheckBox);
    return ui->secondFileNameCheckBox->isChecked();
}

QString OtoFileSaveWidget::secondFileName() const
{

    return ui->secondFileNameEdit->fileName();
}

void OtoFileSaveWidget::setSaveToSrc()
{
    ui->saveToSrcRadioButton->setChecked(true);
}

void OtoFileSaveWidget::setSaveToCustom()
{
    ui->saveToCustomRadioButton->setChecked(true);
}

void OtoFileSaveWidget::setFileName(const QString& value)
{
    ui->saveFileNameEdit->setFileName(value);
}

void OtoFileSaveWidget::setSecondFileNameUsed(bool value)
{
    ui->secondFileNameCheckBox->setChecked(value);
}

void OtoFileSaveWidget::setSecondFileName(const QString& value)
{
    ui->secondFileNameEdit->setFileName(value);
}

bool OtoFileSaveWidget::isSecondFileNameAvailable() const
{
    return secondFileNameAvailable;
}

void OtoFileSaveWidget::setSecondFileNameAvailable(bool value)
{
    secondFileNameAvailable = value;
    refreshSecondFileNameWidgetVisible();
}

void OtoFileSaveWidget::setSecondFileNameCheckBoxText(const QString& text)
{
    ui->secondFileNameCheckBox->setText(text);
}

void OtoFileSaveWidget::refreshSecondFileNameWidgetVisible()
{
    ui->secondFileNameWidget->setVisible(secondFileNameAvailable);
}

OtoFileSaveWidgetWithSecondFileName::OtoFileSaveWidgetWithSecondFileName(QWidget* parent) : OtoFileSaveWidget(parent)
{
    setSecondFileNameAvailable(true);
}

OtoFileSaveWidgetWithSecondFileNameAsDeleted::OtoFileSaveWidgetWithSecondFileNameAsDeleted(QWidget* parent) : OtoFileSaveWidgetWithSecondFileName(parent)
{
    setSecondFileNameCheckBoxText(tr("保存被删除的项到："));
}
