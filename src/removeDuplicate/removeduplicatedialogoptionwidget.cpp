#include "removeduplicatedialogoptionwidget.h"
#include "ui_removeduplicatedialogoptionwidget.h"

RemoveDuplicateDialogOptionWidget::RemoveDuplicateDialogOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::RemoveDuplicateDialogOptionWidget)
{
    ui->setupUi(this);
}

RemoveDuplicateDialogOptionWidget::~RemoveDuplicateDialogOptionWidget()
{
    delete ui;
}

ToolOptions* RemoveDuplicateDialogOptionWidget::getOptions(QObject* parent) const
{
    //TODO: 使用去除Affix替换这里的后缀检测
    auto options = new ToolOptions(parent);

    options->setOption("ignoreSpecificSuffix", ui->ignoreSpecificSuffixCheckBox->isChecked());
    options->setOption("suffixList", ui->suffixListWidget->getData());
    options->setOption("bottomPitch", QString("%1%2").arg(ui->bottomPitchComboBox->currentText()).arg(ui->bottomPitchSpinBox->value()));
    options->setOption("topPitch", QString("%1%2").arg(ui->topPitchComboBox->currentText()).arg(ui->topPitchSpinBox->value()));
    options->setOption("pitchCaseSensitive", ui->caseSensitiveCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
    options->setOption("pitchCase", static_cast<int>(ui->caseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower));
    options->setOption("maxDuplicateCount", ui->maxSpinBox->value());
    options->setOption("shouldOrganize", ui->organizeCheckBox->isChecked());
    options->setOption("organizeStartFrom1", ui->organizeStartFrom1CheckBox->isChecked());
    options->setOption("pitchCaseOrganized", static_cast<int>(ui->organizeCaseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower));

    return options;
}

void RemoveDuplicateDialogOptionWidget::setOptions(const ToolOptions* options)
{
    ui->ignoreSpecificSuffixCheckBox->setChecked(options->getOption("ignoreSpecificSuffix").toBool());
    ui->suffixListWidget->setData(options->getOption("suffixList").toStringList());
    ui->ignorePitchSuffixCheckBox->setChecked(options->getOption("ignorePitchSuffix").toBool());
    ui->bottomPitchComboBox->setCurrentText(options->getOption("bottomPitch").toString().at(0));
    ui->bottomPitchSpinBox->setValue(options->getOption("bottomPitch").toString().midRef(1,1).toInt());
    ui->topPitchComboBox->setCurrentText(options->getOption("topPitch").toString().at(0));
    ui->topPitchSpinBox->setValue(options->getOption("topPitch").toString().midRef(1,1).toInt());
    ui->caseSensitiveCheckBox->setChecked(options->getOption("pitchCaseSensitive").toInt() == Qt::CaseSensitive);
    ui->caseComboBox->setCurrentIndex(options->getOption("pitchCase").toInt() == OtoEntryFunctions::Upper ? 0 : 1);
    ui->maxSpinBox->setValue(options->getOption("maxDuplicateCount").toInt());
    ui->organizeCheckBox->setChecked(options->getOption("shouldOrganize").toBool());
    ui->organizeStartFrom1CheckBox->setChecked(options->getOption("organizeStartFrom1").toBool());
    ui->organizeCaseComboBox->setCurrentIndex(options->getOption("pitchCaseOrganized").toInt() == OtoEntryFunctions::Upper ? 0 : 1);
}
