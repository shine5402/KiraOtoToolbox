#include "presetwidgetcontainer.h"
#include "ui_presetwidgetcontainer.h"

PresetWidgetContainer::PresetWidgetContainer(const QMetaObject& optionMetaObj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetWidgetContainer),
    optionMetaObj(optionMetaObj)
{
    ui->setupUi(this);
}

PresetWidgetContainer::~PresetWidgetContainer()
{
    delete ui;
}
