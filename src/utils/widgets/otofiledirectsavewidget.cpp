#include "otofiledirectsavewidget.h"
#include "ui_otofiledirectsavewidget.h"

OtoFileDirectSaveWidget::OtoFileDirectSaveWidget(QWidget *parent) :
    OtoFileSaveWidgetAbstract(parent),
    ui(new Ui::OtoFileDirectSaveWidget)
{
    ui->setupUi(this);
}

OtoFileDirectSaveWidget::~OtoFileDirectSaveWidget()
{
    delete ui;
}

void OtoFileDirectSaveWidget::setInfoText(QString text)
{
    ui->label->setText(text);
}

bool OtoFileDirectSaveWidget::isSecondFileNameAvailable() const
{
    return false;
}

void OtoFileDirectSaveWidget::setSecondFileNameAvailable(bool value)
{
    Q_UNREACHABLE();
    Q_UNUSED(value);
}

void OtoFileDirectSaveWidget::setSecondFileNameCheckBoxText(const QString& text)
{
    Q_UNREACHABLE();
    Q_UNUSED(text);
}

QString OtoFileDirectSaveWidget::secondFileNameUsage() const
{
    Q_UNREACHABLE();
}

void OtoFileDirectSaveWidget::setSecondFileNameUsage(const QString& value)
{
    Q_UNREACHABLE();
    Q_UNUSED(value);
}

OptionContainer OtoFileDirectSaveWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("isSaveToSrc", true);
    options.setOption("isSaveToCustom", false);
    options.setOption("isSecondFileNameUsed", false);
    //options.setOption("precision", ui->precisionSpinBox->value());
    return options;
}

void OtoFileDirectSaveWidget::setOptions(const OptionContainer& options)
{
    //ui->precisionSpinBox->setValue(options.getOption("precision", 3).toInt());
    Q_UNUSED(options)
}


