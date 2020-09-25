#include "otofilemultipleloadwidget.h"
#include "ui_otofilemultipleloadwidget.h"

OtoFileMultipleLoadWidget::OtoFileMultipleLoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtoFileMultipleLoadWidget)
{
    ui->setupUi(this);
}

OtoFileMultipleLoadWidget::~OtoFileMultipleLoadWidget()
{
    delete ui;
}
