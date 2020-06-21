#include "overlapbatchsetdialogoptionwidget.h"
#include "ui_overlapbatchsetdialogoptionwidget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

OverlapBatchSetDialogOptionWidget::OverlapBatchSetDialogOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::OverlapBatchSetDialogOptionWidget)
{
    ui->setupUi(this);
    connect(ui->setStartWithPresetComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OverlapBatchSetDialogOptionWidget::switchPreset);
    connect(ui->setStartWithLoadFromFileRadioButton, &QRadioButton::toggled, this, &OverlapBatchSetDialogOptionWidget::clearWorkingStartList);
    connect(ui->setStartWithPresetRadioButton, &QRadioButton::toggled, this, &OverlapBatchSetDialogOptionWidget::switchToUsePreset);
    connect(ui->setStartWithInputButton, &QPushButton::clicked, this, &OverlapBatchSetDialogOptionWidget::getStartListFromUserInput);
    loadPreset();
    if (!presetList.isEmpty()){
        ui->setStartWithPresetComboBox->addItems([&]() -> QStringList{
                                                     QStringList items;
                                                     for (auto i : presetList)
                                                     {
                                                         items.append(i.name);
                                                     }
                                                     return items;
                                                 }());
        ui->setStartWithPresetComboBox->setCurrentIndex(0);
    }
    else
    {
        ui->setStartWithPresetComboBox->addItem(tr("（无）"));
        ui->setStartWithPresetComboBox->setEnabled(false);
        ui->setStartWithPresetRadioButton->setEnabled(false);
        ui->setStartWithLoadFromFileRadioButton->setChecked(true);
    }
    startListModel.setStringList(*workingStartList);
    ui->setStartWithListView->setModel(&startListModel);
}

OverlapBatchSetDialogOptionWidget::~OverlapBatchSetDialogOptionWidget()
{
    delete ui;
}

ToolOptions* OverlapBatchSetDialogOptionWidget::getOptions(QObject* parent) const
{
    auto options = new OverlapBatchSetOptions(parent);

    options->setOverlapStartWith = ui->setStartWithCheckBox->isChecked();
    options->startWithPatternList = *workingStartList;
    options->startWithMatchStartAlias = ui->matchStartOtoCheckBox->isChecked();
    options->makeOneThird = ui->OneThirdCheckBox->isChecked();

    return options;
}

void OverlapBatchSetDialogOptionWidget::setOptions(const ToolOptions* options)
{
    auto specificOptions = qobject_cast<const OverlapBatchSetOptions*>(options);
    if (!specificOptions)
        return;
    ui->setStartWithCheckBox->setChecked(specificOptions->setOverlapStartWith);
    ui->setStartWithInputRadioButton->setChecked(true);
    notPresetStartList = specificOptions->startWithPatternList;
    ui->matchStartOtoCheckBox->setChecked(specificOptions->startWithMatchStartAlias);
    ui->OneThirdCheckBox->setChecked(specificOptions->makeOneThird);
}

void OverlapBatchSetDialogOptionWidget::switchPreset(int index)
{
    setWorkingStartList(&presetList.at(index).content);
}

void OverlapBatchSetDialogOptionWidget::clearWorkingStartList()
{
    setWorkingStartList(&emptyStringList);
}

void OverlapBatchSetDialogOptionWidget::loadStartListFromFile()
{
    auto path = QFileDialog::getOpenFileName(this, tr("选择文件"),{},tr("文本文件 (*.txt);;所有文件 (*.*)"));
    if (!path.isEmpty())
    {
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            auto data = file.readAll();
            notPresetStartList = QString::fromUtf8(data).split("\n",QString::SkipEmptyParts);
            setWorkingStartList(&notPresetStartList);
            ui->setStartWithListView->setEnabled(true);
        }
        else {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::critical(this,tr("读取失败"),tr("无法打开指定的文件。"));

        }
    }
}

void OverlapBatchSetDialogOptionWidget::switchToUsePreset()
{
    switchPreset(ui->setStartWithPresetComboBox->currentIndex());
}

void OverlapBatchSetDialogOptionWidget::getStartListFromUserInput()
{
    bool ok = false;
    auto result = QInputDialog::getMultiLineText(this, tr("输入开头列表"),tr("请输入要被匹配的开头字符串的列表，一行一个。"),workingStartList->join("\n"),&ok);
    if (ok)
    {
        notPresetStartList = result.split("\n",QString::SkipEmptyParts);
        setWorkingStartList(&notPresetStartList);
    }
}
