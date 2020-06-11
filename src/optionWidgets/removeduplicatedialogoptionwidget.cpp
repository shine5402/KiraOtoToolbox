#include "removeduplicatedialogoptionwidget.h"
#include "ui_removeduplicatedialogoptionwidget.h"

RemoveDuplicateDialogOptionWidget::RemoveDuplicateDialogOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoveDuplicateDialogOptionWidget)
{
    ui->setupUi(this);
}

RemoveDuplicateDialogOptionWidget::~RemoveDuplicateDialogOptionWidget()
{
    delete ui;
}

RemoveDuplicateDialogOptionWidget::OptionStruct RemoveDuplicateDialogOptionWidget::getOptions() const
{
    OptionStruct options{};

    options.ignoreSpecificSuffix = ui->ignoreSpecificSuffixCheckBox->isChecked();
    options.suffixList = ui->suffixListWidget->getData();
    options.ignorePitchSuffix = ui->ignorePitchSuffixCheckBox->isChecked();
    options.bottomPitch = QString("%1%2").arg(ui->bottomPitchComboBox->currentText()).arg(ui->bottomPitchSpinBox->value());
    options.topPitch = QString("%1%2").arg(ui->topPitchComboBox->currentText()).arg(ui->topPitchSpinBox->value());
    options.pitchCaseSensitive = ui->caseSensitiveCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    options.pitchCase = ui->caseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower;
    options.maxDuplicateCount = ui->maxSpinBox->value();
    options.shouldOrganize = ui->organizeCheckBox->isChecked();
    options.organizeStartFrom1 = ui->organizeStartFrom1CheckBox->isChecked();
    options.pitchCaseOrganized = ui->organizeCaseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower;

    return options;
}

void RemoveDuplicateDialogOptionWidget::setOptions(const RemoveDuplicateDialogOptionWidget::OptionStruct& options)
{
    ui->ignoreSpecificSuffixCheckBox->setChecked(options.ignoreSpecificSuffix);
    ui->suffixListWidget->setData(options.suffixList);
    ui->ignorePitchSuffixCheckBox->setChecked(options.ignorePitchSuffix);
    ui->bottomPitchComboBox->setCurrentText(options.bottomPitch.at(0));
    ui->bottomPitchSpinBox->setValue(options.bottomPitch.midRef(1,1).toInt());
    ui->topPitchComboBox->setCurrentText(options.topPitch.at(0));
    ui->topPitchSpinBox->setValue(options.topPitch.midRef(1,1).toInt());
    ui->caseSensitiveCheckBox->setChecked(options.pitchCaseSensitive == Qt::CaseSensitive);
    ui->caseComboBox->setCurrentIndex(options.pitchCase == OtoEntryFunctions::Upper ? 0 : 1);
    ui->maxSpinBox->setValue(options.maxDuplicateCount);
    ui->organizeCheckBox->setChecked(options.shouldOrganize);
    ui->organizeStartFrom1CheckBox->setChecked(options.organizeStartFrom1);
    ui->organizeCaseComboBox->setCurrentIndex(options.pitchCaseOrganized == OtoEntryFunctions::Upper ? 0 : 1);
}
