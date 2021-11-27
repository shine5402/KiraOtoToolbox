#include "otofilesavewidget.h"
#include "ui_otofilesavewidget.h"

OtoFileSaveWidget::OtoFileSaveWidget(QWidget *parent) :
    OtoFileSaveWidgetAbstract(parent),
    ui(new Ui::OtoFileSaveWidget)
{
    ui->setupUi(this);
    refreshSecondFileNameWidgetVisible();
}

OtoFileSaveWidget::~OtoFileSaveWidget()
{
    delete ui;
}

bool OtoFileSaveWidget::isSecondFileNameAvailable() const
{
    return m_secondFileNameAvailable;
}

void OtoFileSaveWidget::setSecondFileNameAvailable(bool value)
{
    m_secondFileNameAvailable = value;
    refreshSecondFileNameWidgetVisible();
}

void OtoFileSaveWidget::setSecondFileNameCheckBoxText(const QString& text)
{
    ui->secondFileNameCheckBox->setText(text);
}

void OtoFileSaveWidget::refreshSecondFileNameWidgetVisible()
{
    ui->secondFileNameWidget->setVisible(m_secondFileNameAvailable);
}



QString OtoFileSaveWidget::secondFileNameUsage() const
{
    return m_secondFileNameUsage;
}

void OtoFileSaveWidget::setSecondFileNameUsage(const QString& value)
{
    m_secondFileNameUsage = value;
}

OptionContainer OtoFileSaveWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("isSaveToSrc", ui->saveToSrcRadioButton->isChecked());
    options.setOption("isSaveToCustom", ui->saveToCustomRadioButton->isChecked());
    options.setOption("fileName", ui->saveFileNameEdit->fileName());
    options.setOption("isSecondFileNameAvailable", m_secondFileNameAvailable);
    options.setOption("isSecondFileNameUsed", ui->secondFileNameCheckBox->isChecked());
    options.setOption("secondFileName", ui->secondFileNameEdit->fileName());
    //options.setOption("precision", ui->precisionSpinBox->value());
    options.setOption("secondFileNameUsage", m_secondFileNameUsage);
    return options;
}

void OtoFileSaveWidget::setOptions(const OptionContainer& options)
{
    ui->saveToSrcRadioButton->setChecked(options.getOption("isSaveToSrc", true).toBool());
    ui->saveToCustomRadioButton->setChecked(options.getOption("isSaveToCustom", false).toBool());
    ui->saveFileNameEdit->setFileName(options.getOption("fileName").toString());
    if (options.exists("isSecondFileNameAvailable"))
        setSecondFileNameAvailable(options.getOption("isSecondFileNameAvailable").toBool());
    if (isSecondFileNameAvailable())
    {
        ui->secondFileNameCheckBox->setChecked(options.getOption("isSecondFileNameUsed", false).toBool());
        ui->secondFileNameEdit->setFileName(options.getOption("secondFileName").toString());
        setSecondFileNameUsage(options.getOption("secondFileNameUsage").toString());
    }
    //ui->precisionSpinBox->setValue(options.getOption("precision", 3).toInt());
}

OtoFileSaveWidgetWithSecondFileName::OtoFileSaveWidgetWithSecondFileName(QWidget* parent) : OtoFileSaveWidget(parent)
{
    setSecondFileNameAvailable(true);
}

OtoFileSaveWidgetWithSecondFileNameAsDeleted::OtoFileSaveWidgetWithSecondFileNameAsDeleted(QWidget* parent) : OtoFileSaveWidgetWithSecondFileName(parent)
{
    setSecondFileNameCheckBoxText(tr("Save deleted entries to:"));
    setSecondFileNameUsage(tr("Save deleted entries"));
}
