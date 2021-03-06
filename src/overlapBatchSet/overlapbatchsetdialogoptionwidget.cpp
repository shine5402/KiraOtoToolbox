#include "overlapbatchsetdialogoptionwidget.h"
#include "ui_overlapbatchsetdialogoptionwidget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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

const QStringList OverlapBatchSetDialogOptionWidget::emptyStringList{};

OverlapBatchSetDialogOptionWidget::~OverlapBatchSetDialogOptionWidget()
{
    delete ui;
}

OptionContainer OverlapBatchSetDialogOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("ifSetOverlapStartWith", ui->setStartWithCheckBox->isChecked());
    options.setOption("overlapStartWith", ui->setStartWithSpinBox->value());
    options.setOption("startWithPatternList", *workingStartList);
    options.setOption("ifMatchStartOto", ui->matchStartOtoCheckBox->isChecked());
    options.setOption("makeOneThird", ui->OneThirdCheckBox->isChecked());
    //以下的options是UI记录状态用，对worker来说意义不大
    options.setOption("ui_patternList_usingPreset", ui->setStartWithPresetRadioButton->isChecked());
    options.setOption("ui_patternList_currentPreset", ui->setStartWithPresetComboBox->currentIndex());
    options.setOption("ui_patternList_usingFile", ui->setStartWithLoadFromFileRadioButton->isChecked());
    options.setOption("ui_patternList_usingUserInput", ui->setStartWithInputRadioButton->isChecked());
    return options;
}

void OverlapBatchSetDialogOptionWidget::setOptions(const OptionContainer& options)
{
    ui->setStartWithCheckBox->setChecked(options.getOption("ifSetOverlapStartWith").toBool());
    ui->setStartWithSpinBox->setValue(options.getOption("overlapStartWith").toDouble());

    ui->setStartWithPresetRadioButton->setChecked(options.getOption("ui_patternList_usingPreset", true).toBool());
    ui->setStartWithPresetComboBox->setCurrentIndex(options.getOption("ui_patternList_currentPreset", 0).toInt());
    ui->setStartWithLoadFromFileRadioButton->setChecked(options.getOption("ui_patternList_usingFile", false).toBool());
    ui->setStartWithInputRadioButton->setChecked(options.getOption("ui_patternList_usingUserInput",false).toBool());
    notPresetStartList = options.getOption("startWithPatternList").toStringList();

    ui->matchStartOtoCheckBox->setChecked(options.getOption("ifMatchStartOto").toBool());
    ui->OneThirdCheckBox->setChecked(options.getOption("makeOneThird").toBool());
}

void OverlapBatchSetDialogOptionWidget::setWorkingStartList(const QStringList* list)
{
    workingStartList = list;
    startListModel.setStringList(*workingStartList);
}

//TODO: 更通用的预设系统 使用Model等来解耦合？
void OverlapBatchSetDialogOptionWidget::loadPreset()
{
    QFile file(":/overlap_start_preset/preset_list.json");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        auto data = file.readAll();
        QJsonParseError error;
        auto jsonDoc = QJsonDocument::fromJson(data, &error);
        if (!jsonDoc.isNull())
        {
            if (jsonDoc.isArray())
            {
                auto array = jsonDoc.array();
                for (auto value : array)
                {
                    auto obj = value.toObject();
                    auto name = obj.value("name").toString();
                    auto path = obj.value("path").toString();
                    if (name.isEmpty() || path.isEmpty())
                    {
#ifdef SHINE5402OTOBOX_TEST
                        Q_ASSERT(false);
#endif
                        QMessageBox::warning(this,tr("有预设读取失败"),tr("预设描述值至少有一项为空。出现问题的预设将无法使用。"));
                        continue;
                    }
                    QFile file(path);
                    if (file.open(QFile::ReadOnly | QFile::Text))
                    {
                        auto data = file.readAll();
                        if (data.isEmpty())
                        {
#ifdef SHINE5402OTOBOX_TEST
                            Q_ASSERT(false);
#endif
                            QMessageBox::warning(this,tr("有预设读取失败"),tr("预设值为空。出现问题的预设将无法使用。"));
                        }
                        presetList.append({name, QString::fromUtf8(data).split("\n",Qt::SkipEmptyParts)});
                    }
                    else
                    {
#ifdef SHINE5402OTOBOX_TEST
                        Q_ASSERT(false);
#endif
                        QMessageBox::warning(this,tr("有预设读取失败"),tr("读取预设"));
                    }
                    //presetList.append({obj.value("name")})
                }
            }
            else
            {
#ifdef SHINE5402OTOBOX_TEST
                Q_ASSERT(false);
#endif
                QMessageBox::warning(this, tr("预设清单读取失败"),tr("解析预设清单时出现错误：根元素不是Array。预设将不可用。"));
            }
        }
        else
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::warning(this, tr("预设清单读取失败"),tr("解析预设清单时出现错误，错误说明为 %1。预设将不可用。").arg(error.errorString()));
        }
    }
    else
    {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::warning(this, tr("预设清单读取失败"),tr("程序无法打开预设清单文件，预设将不可用。"));
    }
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
            notPresetStartList = QString::fromUtf8(data).split("\n",Qt::SkipEmptyParts);
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
        notPresetStartList = result.split("\n",Qt::SkipEmptyParts);
        setWorkingStartList(&notPresetStartList);
    }
}
