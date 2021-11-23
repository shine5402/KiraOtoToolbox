#include "chaintooloptionwidget.h"
#include "ui_chaintooloptionwidget.h"
#include "utils/dialogs/listviewdialog.h"
#include "chainstepsmodel.h"
#include <QDialogButtonBox>
#include <QGroupBox>
#include "toolBase/toolmanager.h"
#include <fplus/fplus.hpp>
#include "utils/misc/fplusAdapter.h"
#include <QJsonArray>
#include <toolBase/tooldialogadapter.h>
#include <QMessageBox>
#include "chaininvaliddialogadapter.h"
#include <toolBase/tooloptionwidget.h>
#include <toolBase/presetwidgetcontainer.h>

ChainToolOptionWidget::ChainToolOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::ChainToolOptionWidget)
{
    ui->setupUi(this);
    stepsModel = new ChainStepsModel({}, this);
    ui->toolListView->setModel(stepsModel);

    connect(ui->addButton, &QPushButton::clicked, this, &ChainToolOptionWidget::addStep);
    connect(ui->removeButton, &QPushButton::clicked, this, &ChainToolOptionWidget::removeCurrentStep);
    connect(ui->moveUpButton, &QPushButton::clicked, this, &ChainToolOptionWidget::moveUpCurrentStep);
    connect(ui->moveDownButton, &QPushButton::clicked, this, &ChainToolOptionWidget::moveDownCurrentStep);
    connect(ui->adjustSettingsButton, &QPushButton::clicked, this, qOverload<>(&ChainToolOptionWidget::openStepSettings));
    connect(ui->toolListView, &QListView::doubleClicked, this, qOverload<>(&ChainToolOptionWidget::openStepSettings));
}

ChainToolOptionWidget::~ChainToolOptionWidget()
{
    delete ui;
}

OptionContainer ChainToolOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("steps", QVariant::fromValue(stepsModel->getSteps()));

    return options;
}

void ChainToolOptionWidget::setOptions(const OptionContainer& options)
{
    stepsModel->setSteps(options.getOption("steps").value<QVector<ChainElement>>());
}

QJsonObject ChainToolOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonArray jsonArray;
    auto steps = options.getOption("steps").value<QVector<ChainElement>>();
    for (const auto& step: std::as_const(steps)){
        QJsonObject stepJsonObj;
        stepJsonObj.insert("stepAdapterClassName", step.tool.toolAdapterMetaObj.className());
        stepJsonObj.insert("options", std::unique_ptr<ToolOptionWidget>(step.tool.getToolOptionWidgetInstance(nullptr))->optionsToJson(step.options));
        jsonArray.append(stepJsonObj);
    }
    return {{"steps", jsonArray}};
}

OptionContainer ChainToolOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    auto registeredTools = ToolManager::getManager()->getTools();
    QHash<QString, int> knownToolMap;//className to registerId
    for (auto i = 0; i < registeredTools.count(); ++i){
        knownToolMap.insert(registeredTools.at(i).toolAdapterMetaObj.className(), i);
    }

    auto stepsJsonArray = json.value("steps").toArray();
    QVector<ChainElement> steps;
    for (const auto& stepJson : std::as_const(stepsJsonArray)){
        auto obj = stepJson.toObject();
        auto className = obj.value("stepAdapterClassName").toString();

        //If invalid tool in preset exists here
        if (className == "ChainInvalidDialogAdapter")
        {
            auto originalOptionsJson = obj.value("options").toObject();
            auto originalClassName = obj.value("originalClassName").toString();
            //These two insert would act like replace. And if it still not exists, we would convert it to invalid below.
            obj.insert("className", originalClassName);
            obj.insert("options", originalOptionsJson);
        }

        //If there is an unknown tool
        if (!knownToolMap.contains(className)){
            OptionContainer options;
            options.setOption("originalClassName", className);
            options.setOption("options", obj.value("options").toObject());
            steps.append({ChainInvalidDialogAdapter::staticMetaObject, {}});
            continue;
        }

        auto tool = registeredTools.at(knownToolMap.value(className));
        auto options = std::unique_ptr<ToolOptionWidget>(tool.getToolOptionWidgetInstance(nullptr))->jsonToOptions(obj.value("options").toObject());
        steps.append({tool.toolAdapterMetaObj, options});
    }
    OptionContainer options;
    options.setOption("steps", QVariant::fromValue(steps));
    return options;
}

int ChainToolOptionWidget::optionJsonVersion() const
{
    return 1;
}

int ChainToolOptionWidget::getCurrentRow() const
{
    return ui->toolListView->selectionModel()->currentIndex().row();
}

void ChainToolOptionWidget::setCurrentRow(int row)
{
    auto selectionModel = ui->toolListView->selectionModel();
    selectionModel->setCurrentIndex(selectionModel->model()->index(row, 0, QModelIndex{}),
                                    QItemSelectionModel::Clear | QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows);
}

void ChainToolOptionWidget::addStep()
{
    auto registeredTools = ToolManager::getManager()->getTools();
    auto availableTools = fplus::transform([](Tool tool)->ChainElement{
            return {tool, {}};
    }, registeredTools);
    auto model = new ChainStepsModel(availableTools, this);
    auto dialog = new ListViewDialog(this, model, tr("选择一个工具"), tr("从下面的可用工具中选择一个作为操作文件的新步骤。"), QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dialog->setDoubleClickAsAccept(true);
    if (dialog->exec() == QDialog::Accepted)
    {
        stepsModel->addStep(availableTools.at(dialog->currentRow()));
        openStepSettings(stepsModel->stepCount() - 1);
        emit userSettingsChanged();
    }
}

void ChainToolOptionWidget::removeCurrentStep()
{
    stepsModel->removeStep(getCurrentRow());
    emit userSettingsChanged();
}

void ChainToolOptionWidget::moveUpCurrentStep()
{
    stepsModel->moveUpStep(getCurrentRow());
    emit userSettingsChanged();
}

void ChainToolOptionWidget::moveDownCurrentStep()
{
    stepsModel->moveDownStep(getCurrentRow());
    emit userSettingsChanged();
}

void ChainToolOptionWidget::openStepSettings(int index)
{
    Q_ASSERT(!pendingStepSetting.ptrDialog);
    if (pendingStepSetting.ptrDialog)
    {
        return;
    }

    auto dialog = new QDialog(this);
    dialog->setModal(true);
    dialog->setWindowTitle(tr("调整“%1”（位于 第 %2 项）的设置")
                           .arg(stepsModel->getStep(index).toolName(),
                                QString::number(index + 1)));

    auto dialogLayout = new QVBoxLayout(dialog);

    auto groupBox = new QGroupBox(tr("行为调整（设置会自动保存）"), dialog);

    dialogLayout->addWidget(groupBox);
    constexpr auto GROUPBOX_INDEX = 0;
    constexpr auto GROUPBOX_STRETCH = 1;
    dialogLayout->setStretch(GROUPBOX_INDEX, GROUPBOX_STRETCH);//让GroupBox的权重变大

    auto groupBoxLayout = new QVBoxLayout(groupBox);
    auto optionWidgetMetaObj = stepsModel->getStep(index).tool.getToolOptionWidgetMetaObj();
    auto presetContainer = new PresetWidgetContainer(optionWidgetMetaObj, groupBox);
    auto options = stepsModel->getStep(index).options;
    if (!options.isEmpty())
        presetContainer->setWorkingOptions(options);
    groupBoxLayout->addWidget(presetContainer);
    groupBox->setLayout(groupBoxLayout);

    auto buttonBox = new QDialogButtonBox(dialog);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    dialogLayout->addWidget(buttonBox);

    dialog->setLayout(dialogLayout);

    dialog->setAttribute(Qt::WA_DeleteOnClose, false);//As we will need its member's info later.

    connect(dialog, &QDialog::finished, this, &ChainToolOptionWidget::handleStepSettingsDone);

    dialog->open();
    pendingStepSetting.ptrPresetContainer = presetContainer;
    pendingStepSetting.ptrDialog = dialog;
    pendingStepSetting.index = index;
}

void ChainToolOptionWidget::openStepSettings()
{
    if (getCurrentRow() >= 0 && getCurrentRow() < stepsModel->stepCount()){
        openStepSettings(getCurrentRow());
    }
}

void ChainToolOptionWidget::handleStepSettingsDone(int result)
{
    if (result == QDialog::Accepted){
        stepsModel->setStepOptions(pendingStepSetting.index, pendingStepSetting.ptrPresetContainer->optionWidget()->getOptions());
        emit userSettingsChanged();
    }
    pendingStepSetting.ptrDialog->deleteLater();
    pendingStepSetting = {};
}

