#include "cv_vcpartsplitoptionwidget.h"
#include "ui_cv_vcpartsplitoptionwidget.h"

CV_VCPartSplitOptionWidget::CV_VCPartSplitOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::CV_VCPartSplitOptionWidget)
{
    ui->setupUi(this);
}

CV_VCPartSplitOptionWidget::~CV_VCPartSplitOptionWidget()
{
    delete ui;
}

OptionContainer CV_VCPartSplitOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("isSeeBeginPatternAsCV", ui->seeBeginPatternAsCVCheckBox->isChecked());
    options.setOption("seeBeginPatternAsCVContent", ui->seeBeginPatternAsCVContentWidget->getData());
    options.setOption("isSeeEndPatternAsCV", ui->seeEndPatternAsCVCheckBox->isChecked());
    options.setOption("seeEndPatternAsCVContent", ui->seeEndPatternAsCVContentWidget->getData());
    return options;
}

void CV_VCPartSplitOptionWidget::setOptions(const OptionContainer& options)
{
    ui->seeBeginPatternAsCVCheckBox->setChecked(options.getOption("isSeeBeginPatternAsCV", true).toBool());
    ui->seeBeginPatternAsCVContentWidget->setData(options.getOption("seeBeginPatternAsCVContent", QStringList{"-","・"}).toStringList());
    ui->seeEndPatternAsCVCheckBox->setChecked(options.getOption("isSeeEndPatternAsCV", true).toBool());
    ui->seeEndPatternAsCVContentWidget->setData(options.getOption("seeEndPatternAsCVContent", QStringList{"-","L"}).toStringList());
}
