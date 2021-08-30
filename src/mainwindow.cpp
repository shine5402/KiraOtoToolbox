#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "toolBase/tooldialog.h"
#include "removeDuplicate/removeduplicatedialogadapter.h"
#include "overlapBatchSet/overlapbatchsetdialogadapter.h"
#include <QMessageBox>
#include "removeAffix/removeaffixdialogadapter.h"
#include "addAffix/addaffixdialogadapter.h"
#include "toolBase/toolmanager.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef NDEBUG
    ui->actionDebug->setVisible(false);
#else
    connect(ui->actionDebug, &QAction::triggered, this, &MainWindow::debugFunction);
#endif

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(ui->actionAbout_Qt, &QAction::triggered, this, &MainWindow::showAboutQtDialog);
    connect(ui->actionDonate, &QAction::triggered, this, &MainWindow::showDonationPage);
    connect(ui->actionUpdate, &QAction::triggered, this, &MainWindow::showUpdatePage);

    auto buttonGroup = new QButtonGroup(this);

    auto availableTools = ToolManager::getManager()->getTools();
    auto toolGroups = ToolManager::getManager()->getToolGroups();
    auto groups = ToolManager::getManager()->getToolGroupNamesInRegisterOrder();
    for (int groupID = 0; groupID < groups.count(); ++groupID){
        auto group = groups.at(groupID);
        auto groupBox = new QGroupBox(group.isEmpty() ? tr("未分类") : group, this);
        auto groupBoxLayout = new QVBoxLayout(groupBox);
        auto tools = toolGroups.values(group);
        std::reverse(tools.begin(), tools.end());
        for (const auto& tool : tools)
        {
            auto button = new QPushButton(tool.toolName(), this);
            buttonGroup->addButton(button, availableTools.indexOf(tool));
            groupBoxLayout->addWidget(button);
        }
        ui->toolLayout->insertWidget(groupID + 1, groupBox);//1 表示在第一个spacer后面
    }

    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), [buttonGroup, this](QAbstractButton* button){
        auto tools = ToolManager::getManager()->getTools();
        (new ToolDialog(tools.at(buttonGroup->id(button)).getAdapterInstance(this), this))->open();
    });
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::exit()
{
    qApp->exit();
}

void MainWindow::showAboutDialog()
{
#ifdef VERSION_BETA
    auto versionStr = qApp->applicationVersion() + " (BETA)";
#else
    auto versionStr = qApp->applicationVersion();
#endif
    QMessageBox::about(this, tr("关于"), tr(
R"(<h2>shine_5402 的 oto 工具箱</h2>

<p>Copyright 2020 <a href="https://shine5402.top/about-me">shine_5402</a></p>
<p>版本 %1</p>
<h3>关于</h3>
<p>一个个人自用向的操作UTAU用声音资料库的原音设定文件oto.ini的工具箱</p>
<h3>许可</h3>
<p>本程序是自由软件：你可以在遵守由自由软件基金会发布的GNU通用公共许可证版本3（或者更新的版本）的情况下重新分发和/或修改本程序。</p>
<p>本程序的发布旨在能够派上用场，但是<span style="font-weight: bold;">并不对此作出任何担保</span>；乃至也没有对<span style="font-weight: bold;">适销性</span>或<span style="font-weight: bold;">特定用途适用性</span>的默示担保。参见GNU通用公共许可证来获得更多细节。</p>
<p>在得到本程序的同时，您应该也收到了一份GNU通用公共许可证的副本。如果没有，请查阅<a href="https://www.gnu.org/licenses/">https://www.gnu.org/licenses/</a>。</p>

<h3>本程序使用的开源软件库</h3>
<ul>
<li>Qt, The Qt Company Ltd, under LGPL v3.</li>
<li>QKiraUTAUUtils, shine_5402, under LGPL v3</li>
<li><a href="https://github.com/google/diff-match-patch">Diff-Match-Patch</a>, Copyright 2018 The diff-match-patch Authors, under the Apache License, Version 2.0</li>
<li><a href="https://github.com/Dobiasd/FunctionalPlus">FunctionalPlus</a>, BSL-1.0 License</li>
</ul>
)"
).arg(versionStr));
}

void MainWindow::showAboutQtDialog()
{
    QMessageBox::aboutQt(this, tr("关于 Qt"));
}

void MainWindow::showDonationPage()
{
    QDesktopServices::openUrl(QUrl{"https://afdian.net/@shine5402"});
}

void MainWindow::showUpdatePage()
{
    QDesktopServices::openUrl(QUrl{"https://github.com/shine5402/Shine5402OtoToolBox/releases"});
}

#ifndef NDEBUG
void MainWindow::debugFunction()
{

}
#endif
