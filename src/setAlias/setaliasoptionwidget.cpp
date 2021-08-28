#include "setaliasoptionwidget.h"
#include "ui_setaliastooloptionwidget.h"

SetAliasOptionWidget::SetAliasOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::SetAliasToolOptionWidget)
{
    ui->setupUi(this);
}

SetAliasOptionWidget::~SetAliasOptionWidget()
{
    delete ui;
}


OptionContainer SetAliasOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("renamingRule", ui->ruleLineEdit->text());
    options.setOption("cutHeadCount", ui->headCutSpinBox->value());
    options.setOption("cutTailCount", ui->tailCutSpinBox->value());
    options.setOption("strShouldRemove", ui->removeStrLineEdit->text());
    options.setOption("strShouldRemoveIsRegex", ui->removeStrRegexCheckBox->isChecked());
    options.setOption("onlyForEmpty", ui->emptyOnlyCheckBox->isChecked());
    return options;
}

void SetAliasOptionWidget::setOptions(const OptionContainer& options)
{
    ui->ruleLineEdit->setText(options.getOption("renamingRule").toString());
    ui->headCutSpinBox->setValue(options.getOption("cutHeadCount").toInt());
    ui->tailCutSpinBox->setValue(options.getOption("cutTailCount").toInt());
    ui->removeStrLineEdit->setText(options.getOption("strShouldRemove").toString());
    ui->removeStrRegexCheckBox->setChecked(options.getOption("strShouldRemoveIsRegex").toBool());
    ui->emptyOnlyCheckBox->setChecked(options.getOption("onlyForEmpty").toBool());
}
