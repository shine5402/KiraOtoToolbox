#include "chaintooloptionwidget.h"
#include "ui_chaintooloptionwidget.h"
#include "utils/dialogs/listviewdialog.h"
#include "chainstepsmodel.h"
#include <QDialogButtonBox>
#include <QGroupBox>
#include "toolBase/toolmanager.h"
#include <fplus/fplus.hpp>
#include "utils/misc/fplusAdapter.h"

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
            return {*tool.getDialogAdapter()->metaObject(), *tool.getModifyWorker()->metaObject(), *tool.getOptionWidget()->metaObject(), {}};
    }, registeredTools);
    auto model = new ChainStepsModel(availableTools, this);
    auto dialog = new ListViewDialog(this, model, tr("选择一个工具"), tr("从下面的可用工具中选择一个作为操作文件的新步骤。"), QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    if (dialog->exec() == QDialog::Accepted)
    {
        stepsModel->addStep(availableTools.at(dialog->currentRow()));
        openStepSettings(stepsModel->stepCount() - 1);
    }
}

void ChainToolOptionWidget::removeCurrentStep()
{
    stepsModel->removeStep(getCurrentRow());
}

void ChainToolOptionWidget::moveUpCurrentStep()
{
    stepsModel->moveUpStep(getCurrentRow());
}

void ChainToolOptionWidget::moveDownCurrentStep()
{
    stepsModel->moveDownStep(getCurrentRow());
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
    auto optionWidget = qobject_cast<ToolOptionWidget *>(stepsModel->getStep(index).toolOptionWidgetMetaObj.newInstance(Q_ARG(QWidget*, this)));
    optionWidget->setOptions(stepsModel->getStep(index).options);
    groupBoxLayout->addWidget(optionWidget);
    groupBox->setLayout(groupBoxLayout);

    auto buttonBox = new QDialogButtonBox(dialog);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    dialogLayout->addWidget(buttonBox);

    dialog->setLayout(dialogLayout);

    dialog->setAttribute(Qt::WA_DeleteOnClose, false);//As we will need its member's info later.

    connect(dialog, &QDialog::finished, this, &ChainToolOptionWidget::handleStepSettingsDone);

    dialog->open();
    pendingStepSetting.ptrOptionWidget = optionWidget;
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
        stepsModel->setStepOptions(pendingStepSetting.index, pendingStepSetting.ptrOptionWidget->getOptions());
    }
    pendingStepSetting.ptrDialog->deleteLater();
    pendingStepSetting = {};
}

