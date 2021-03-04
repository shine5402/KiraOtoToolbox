#include "presetwidget.h"
#include "ui_presetwidget.h"

PresetWidget::PresetWidget(QAbstractItemView* contentView, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetWidget)
{
    ui->setupUi(this);
    changeContentView(contentView);

    connect(ui->presetComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &PresetWidget::presetSwitched);
    connect(ui->extendEditButton, &QAbstractButton::clicked, this, &PresetWidget::extendEditAsked);
    connect(ui->renameButton, &QAbstractButton::clicked, [&](){
        emit presetRenameAsked(ui->presetComboBox->currentIndex());
    });
    connect(ui->copyButton, &QAbstractButton::clicked, [&](){
        emit presetCopyAsked(ui->presetComboBox->currentIndex());
    });
    connect(ui->removeButton, &QAbstractButton::clicked, [&](){
        emit presetRemoveAsked(ui->presetComboBox->currentIndex());
    });
    connect(ui->saveButton, &QAbstractButton::clicked, [&](){
        emit presetSaveAsked(ui->presetComboBox->currentIndex());
    });
}

PresetWidget::~PresetWidget()
{
    delete ui;
}

void PresetWidget::changeContentView(QAbstractItemView* newView)
{
    delete ui->mainLayout->replaceWidget(ui->contentView, newView);
    contentView = newView;
    ui->contentView = newView;
    contentView->setParent(this);
}

QAbstractItemView* PresetWidget::getContentView() const
{
    return contentView;
}
