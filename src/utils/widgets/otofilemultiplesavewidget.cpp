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

bool OtoFileMultipleSaveWidget::isSaveToSrc() const
{
    return true;
}

bool OtoFileMultipleSaveWidget::isSaveToCustom() const
{
    return false;
}

QString OtoFileMultipleSaveWidget::fileName() const
{
    Q_UNREACHABLE();
}

bool OtoFileMultipleSaveWidget::isSecondFileNameUsed() const
{
    return false;
}

QString OtoFileMultipleSaveWidget::secondFileName() const
{
    Q_UNREACHABLE();
}

void OtoFileMultipleSaveWidget::setSaveToSrc()
{
    Q_UNREACHABLE();
}

void OtoFileMultipleSaveWidget::setSaveToCustom()
{
    Q_UNREACHABLE();
}

void OtoFileMultipleSaveWidget::setFileName(const QString& value)
{
    Q_UNREACHABLE();
    Q_UNUSED(value);
}

void OtoFileMultipleSaveWidget::setSecondFileNameUsed(bool value)
{
    Q_UNREACHABLE();
    Q_UNUSED(value);
}

void OtoFileMultipleSaveWidget::setSecondFileName(const QString& value)
{
    Q_UNREACHABLE();
    Q_UNUSED(value);
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


