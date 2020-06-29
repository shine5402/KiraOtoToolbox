#include "removeaffixoptionwidget.h"
#include "ui_removeaffixoptionwidget.h"

RemoveAffixOptionWidget::RemoveAffixOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoveAffixOptionWidget)
{
    ui->setupUi(this);
}

RemoveAffixOptionWidget::~RemoveAffixOptionWidget()
{
    delete ui;
}
