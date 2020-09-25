#include "otofilemultiplesavewidget.h"
#include "ui_otofilemultiplesavewidget.h"

OtoFileMultipleSaveWidget::OtoFileMultipleSaveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtoFileMultipleSaveWidget)
{
    ui->setupUi(this);
}

OtoFileMultipleSaveWidget::~OtoFileMultipleSaveWidget()
{
    delete ui;
}


