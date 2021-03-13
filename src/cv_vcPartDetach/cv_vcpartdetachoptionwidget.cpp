#include "cv_vcpartdetachoptionwidget.h"
#include "ui_cv_vcpartdetachoptionwidget.h"

CV_VCPartDetachOptionWidget::CV_VCPartDetachOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::CV_VCPartDetachOptionWidget)
{
    ui->setupUi(this);
    setOptions(OptionContainer{});
}

CV_VCPartDetachOptionWidget::~CV_VCPartDetachOptionWidget()
{
    delete ui;
}

OptionContainer CV_VCPartDetachOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("isSeePatternAsCV", ui->seePatternAsCVCheckbox->isChecked());
    options.setOption("seePatternAsCVContent", ui->seePatternAsCVContentWidget->getData());
    return options;
}

void CV_VCPartDetachOptionWidget::setOptions(const OptionContainer& options)
{
    ui->seePatternAsCVCheckbox->setChecked(options.getOption("isSeePatternAsCV", true).toBool());
    ui->seePatternAsCVContentWidget->setData(options.getOption("seePatternAsCVContent", QStringList{"-","・"}).toStringList());
}
