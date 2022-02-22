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
#include <kira/i18n/translationmanager.h>
#include <QSettings>
#include <kira/darkmode.h>
#include <kira/updatechecker.h>

void MainWindow::setArgInfoBlock()
{
    auto args = qApp->arguments();

    if (args.count() < 2)
    {
        ui->argInfoBlock->hide();
    }
    else
    {
        args.removeFirst();
        ui->argInfoLabel->setText(tr("<p>It seems like that these filepaths provided in arguments. <br/>"
                                     "These paths will be used as tool's oto data input.</p><code><ul style='margin-left:15px;-qt-list-indent:0;'><li>%1</li></ul></code>").arg(args.count() > 1 ? args.join("</li><li>") : args.at(0)));
    }
}

QMenu* MainWindow::createHelpMenu()
{
    auto helpMenu = new QMenu(tr("Help"), this);
    auto aboutAction = helpMenu->addAction(tr("About"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
    auto aboutQtAction = helpMenu->addAction(tr("About Qt"));
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    helpMenu->addSeparator();
    helpMenu->addMenu(UpdateChecker::createMenuForSchedule());
    auto checkUpdateAction = helpMenu->addAction(tr("Check update now"));
    connect(checkUpdateAction, &QAction::triggered, this, [this](){
        UpdateChecker::checkManully(updateChecker);
    });
    helpMenu->addSeparator();
    auto feedbackAction = helpMenu->addAction(tr("Provide feedback"));
    connect(feedbackAction, &QAction::triggered, this, [](){
        QDesktopServices::openUrl(QUrl{"https://github.com/shine5402/Shine5402OtoToolBox/issues"});
    });

    return helpMenu;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    setArgInfoBlock();

    //Create tool selector ui
    createToolSelectorUI();

    //create language menu
    ui->langButton->setMenu(TranslationManager::getManager()->getI18nMenu());

    //darkMode
    ui->uiThemeButton->setMenu(DarkMode::getDarkModeSettingMenu());
    auto darkModeObserver = DarkMode::getObserver();
    connect(darkModeObserver, &DarkMode::Observer::darkModeChanged, this, &MainWindow::fitUIToDarkMode);
    fitUIToDarkMode(DarkMode::getCurrentMode());

    //Help menu
    auto helpMenu = createHelpMenu();
    ui->helpButton->setMenu(helpMenu);

    //set window titie
    setWindowTitle(tr("%1 ver.%2").arg(qApp->applicationName(), qApp->applicationVersion()));
    if (QStringLiteral(GIT_BRANCH) == QStringLiteral("dev"))
        setWindowTitle(tr("%1 ver.%2").arg(qApp->applicationName(), qApp->applicationVersion() + " [BETA]"));

    updateChecker = new UpdateChecker::GithubReleaseChecker("shine5402", "KiraOtoToolbox", this);
    UpdateChecker::triggerScheduledCheck(updateChecker);
#ifndef NDEBUG
    auto debugAction = new QAction("Debug", this);
    connect(debugAction, &QAction::triggered, debugAction, [](){

    });
    helpMenu->addAction(debugAction);
#endif
}

void MainWindow::createToolSelectorUI()
{
    if (!toolButtonsLayoutResources.isEmpty())
    {
        for (auto i : qAsConst(toolButtonsLayoutResources)){
            auto widget = qobject_cast<QWidget*>(i);
            if (widget)
            {
                ui->toolLayout->removeWidget(widget);
            }
            i->deleteLater();
        }
        toolButtonsLayoutResources.clear();
    }

    auto toolButtonGroup = new QButtonGroup(this);
    toolButtonsLayoutResources.append(toolButtonGroup);

    auto availableTools = ToolManager::getManager()->getTools();
    auto toolGroups = ToolManager::getManager()->getToolGroups();
    auto groups = ToolManager::getManager()->getToolGroupNamesInRegisterOrder();
    for (int groupID = 0; groupID < groups.count(); ++groupID){
        auto group = groups.at(groupID);
        auto groupBox = new QGroupBox(group.isEmpty() ? tr("Uncategorized") : QCoreApplication::translate("TOOL_TYPE", group.toStdString().c_str()), this);
        toolButtonsLayoutResources.append(groupBox);
        auto groupBoxLayout = new QVBoxLayout(groupBox);
        auto tools = toolGroups.values(group);
        std::reverse(tools.begin(), tools.end());
        for (const auto& tool : tools)
        {
            auto button = new QPushButton(tool.toolName(), groupBox);
            toolButtonGroup->addButton(button, availableTools.indexOf(tool));
            groupBoxLayout->addWidget(button);
        }
        ui->toolLayout->insertWidget(groupID, groupBox);//1 stands for behind first spacer in ui layout
    }

    connect(toolButtonGroup, qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), toolButtonGroup, [toolButtonGroup, this](QAbstractButton* button){
        auto tools = ToolManager::getManager()->getTools();
        auto dialog = new ToolDialog(tools.at(toolButtonGroup->id(button)).getAdapterInstance(this), this);
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        dialog->open();
    });



}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::showAboutDialog()
{
    auto isBeta = QStringLiteral(GIT_BRANCH) == QStringLiteral("dev");
    QString versionStr = tr("<p>Version %1%4, <i>branch: %2, commit: %3, build on %5 %6<i></p>")
            .arg(qApp->applicationVersion(), GIT_HASH, GIT_DESCRIBE, isBeta ? "-beta" : "", __DATE__, __TIME__);
    if (isBeta)
        versionStr += tr("<p style=\"color:orange\">You are using a BETA build. "
                         "<b>Use it at your own risk.</b>"
                         " If any problems occured, please provide feedback on Github Issues.</p>");

    QMessageBox::about(this, tr("About"), tr(
                           R"(<h2>KiraOtoToolbox</h2>

<p>Copyright 2021 <a href="https://shine5402.top/about-me">shine_5402</a></p>
%1
<h3>About</h3>
<p>A toolbox for manipulating "oto.ini", the voicebank labeling format for UTAU.</p>
<h3>License</h3>
<<p> This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.<br>
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.<br>
You should have received a copy of the GNU General Public License
along with this program.  If not, see <a href="https://www.gnu.org/licenses/">https://www.gnu.org/licenses/</a>.<br>
 In addition, as a special exception, the copyright holders give
 permission to link the code of portions of this program with the
 OpenSSL library under certain conditions as described in each
 individual source file, and distribute linked combinations
 including the two.<br>
 You must obey the GNU General Public License in all respects
 for all of the code used other than OpenSSL.  If you modify
 file(s) with this exception, you may extend this exception to your
 version of the file(s), but you are not obligated to do so.  If you
 do not wish to do so, delete this exception statement from your
 version.  If you delete this exception statement from all source
 files in the program, then also delete it here.</p>

<h3>3rd party librarays used by this project</h3>
<ul>
<li>Qt %2, The Qt Company Ltd, under LGPL v3.</li>
<li><a href="https://github.com/shine5402/KiraUTAUUtils">KiraUTAUUtils</a>, shine_5402, under LGPL v3</li>
<li><a href="https://github.com/shine5402/KiraCommonUtils">KiraCommmonUtils</a>, shine_5402, mainly under the Apache License, Version 2.0</li>
<li><a href="https://github.com/google/diff-match-patch">Diff-Match-Patch</a>, Copyright 2018 The diff-match-patch Authors, under the Apache License, Version 2.0</li>
<li><a href="https://github.com/Dobiasd/FunctionalPlus">FunctionalPlus</a>, BSL-1.0 License</li>
<li>This product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit. (<a href='http://www.openssl.org'>http://www.openssl.org/</a>)</li>
</ul>

<p>Some icons are provided by <a href="https://icons8.com">icons8</a>.</p>
)"
).arg(versionStr, QT_VERSION_STR));
}


void MainWindow::fitUIToDarkMode(DarkMode::Mode curr)
{
    if (curr == DarkMode::LIGHT)
    {
        ui->logoLabel->setPixmap(QPixmap(":/logo/light"));
        ui->argIconLabel->setPixmap(QPixmap(":/icon/console"));
        auto argInfoPalette = QPalette();
        argInfoPalette.setColor(QPalette::WindowText, QColor("#004970"));
        argInfoPalette.setColor(QPalette::Text, QColor("#004970"));
        ui->argInfoLabel->setPalette(argInfoPalette);
    }
    else
    {
        ui->logoLabel->setPixmap(QPixmap(":/logo/dark"));
        ui->argIconLabel->setPixmap(QPixmap(":/icon/console_dark"));
        auto argInfoPalette = QPalette();
        argInfoPalette.setColor(QPalette::WindowText, QColor("#9fe1ff"));
        argInfoPalette.setColor(QPalette::Text, QColor("#9fe1ff"));
        ui->argInfoLabel->setPalette(argInfoPalette);
    }
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        createToolSelectorUI();
        setArgInfoBlock();
        ui->uiThemeButton->setMenu(DarkMode::getDarkModeSettingMenu());//trigger a text reset
        ui->helpButton->menu()->deleteLater();
        ui->helpButton->setMenu(createHelpMenu());
    }
}
