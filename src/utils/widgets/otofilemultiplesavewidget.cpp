#include "otofilemultiplesavewidget.h"
#include "ui_otofilemultiplesavewidget.h"

OtoFileMultipleSaveWidget::OtoFileMultipleSaveWidget(QWidget *parent) :
    OtoFileSaveWidgetAbstract(parent),
    ui(new Ui::OtoFileMultipleSaveWidget)
{
    ui->setupUi(this);
}

OtoFileMultipleSaveWidget::~OtoFileMultipleSaveWidget()
{
    delete ui;
}

bool OtoFileMultipleSaveWidget::isSecondFileNameAvailable() const
{
    return false;
}

void OtoFileMultipleSaveWidget::setSecondFileNameAvailable(bool value)
{
    Q_UNREACHABLE();
    Q_UNUSED(value);
}

void OtoFileMultipleSaveWidget::setSecondFileNameCheckBoxText(const QString& text)
{
    Q_UNREACHABLE();
    Q_UNUSED(text);
}

QString OtoFileMultipleSaveWidget::secondFileNameUsage() const
{
    Q_UNREACHABLE();
}

void OtoFileMultipleSaveWidget::setSecondFileNameUsage(const QString& value)
{
    Q_UNREACHABLE();
    Q_UNUSED(value);
}

OptionContainer OtoFileMultipleSaveWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("isSaveToSrc", true);
    options.setOption("isSaveToCustom", false);
    options.setOption("isSecondFileNameUsed", false);
    options.setOption("precision", ui->precisionSpinBox->value());
    return options;
}

void OtoFileMultipleSaveWidget::setOptions(const OptionContainer& options)
{
    ui->precisionSpinBox->setValue(options.getOption("precision", 3).toInt());
}


