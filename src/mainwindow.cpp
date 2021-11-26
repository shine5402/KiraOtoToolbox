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
#include "i18n/translationmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(ui->actionAbout_Qt, &QAction::triggered, this, &MainWindow::showAboutQtDialog);
    connect(ui->actionDonate, &QAction::triggered, this, &MainWindow::showDonationPage);
    connect(ui->actionUpdate, &QAction::triggered, this, &MainWindow::showUpdatePage);
    connect(ui->actionSend_feedback, &QAction::triggered, this, &MainWindow::showFeedbackPage);

    //Create tool selector ui
    auto buttonGroup = new QButtonGroup(this);

    auto availableTools = ToolManager::getManager()->getTools();
    auto toolGroups = ToolManager::getManager()->getToolGroups();
    auto groups = ToolManager::getManager()->getToolGroupNamesInRegisterOrder();
    for (int groupID = 0; groupID < groups.count(); ++groupID){
        auto group = groups.at(groupID);
        auto groupBox = new QGroupBox(group.isEmpty() ? tr("Uncategorized") : group, this);
        auto groupBoxLayout = new QVBoxLayout(groupBox);
        auto tools = toolGroups.values(group);
        std::reverse(tools.begin(), tools.end());
        for (const auto& tool : tools)
        {
            auto button = new QPushButton(tool.toolName(), this);
            buttonGroup->addButton(button, availableTools.indexOf(tool));
            groupBoxLayout->addWidget(button);
        }
        ui->toolLayout->insertWidget(groupID + 1, groupBox);//1 stands for behind first spacer in ui layout
    }

    connect(buttonGroup, qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), [buttonGroup, this](QAbstractButton* button){
        auto tools = ToolManager::getManager()->getTools();
        auto dialog = new ToolDialog(tools.at(buttonGroup->id(button)).getAdapterInstance(this), this);
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        dialog->open();
    });

    //create language menu
    auto translations = TranslationManager::getManager()->getTranslations();
    auto i18nMenu = new QMenu(tr("Language"), this);
    auto defaultLang = new QAction("English, built-in");
    defaultLang->setData(-1);
    defaultLang->setCheckable(true);
    i18nMenu->addAction(defaultLang);

    for (auto i = 0; i < translations.count(); ++i)
    {
        auto l = translations.at(i);
        auto langAction = new QAction(QLatin1String("%1, by %2").arg(l.locale().bcp47Name(), l.author()));
        langAction->setData(i);
        langAction->setCheckable(true);
        i18nMenu->addAction(langAction);

    }
    auto setLangActionChecked = [i18nMenu](const Translation& translation){
        auto actions = i18nMenu->actions();
        for (auto action : qAsConst(actions)){
            auto currTr = TranslationManager::getManager()->getTranslation(action->data().toInt());
            action->setChecked(currTr == translation);
        }
    };
    connect(i18nMenu, &QMenu::triggered, [setLangActionChecked](QAction* action){
        auto translation = TranslationManager::getManager()->getTranslation(action->data().toInt());
        translation.install();
        setLangActionChecked(translation);
    });
    ui->menu_Preference->addMenu(i18nMenu);

    TranslationManager::getManager()->getTranslationFor(QLocale::system()).install();
    setLangActionChecked(Translation::getCurrentInstalled());

    //set window titie
    setWindowTitle(tr("%1 ver.%2").arg(qApp->applicationName(), qApp->applicationVersion()));
#ifdef VERSION_BETA
    setWindowTitle(tr("%1 ver.%2").arg(qApp->applicationName(), qApp->applicationVersion() + " [BETA]"));
#endif
#ifndef NDEBUG
    auto debugAction = new QAction("Debug", this);
    ui->menu_Preference->addAction(debugAction);
    connect(debugAction, &QAction::triggered, [](){

    });
#endif
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::showAboutDialog()
{
#ifdef VERSION_BETA
    auto versionStr = qApp->applicationVersion() + " (BETA) </p><p style=\"color:orange\">You are using a test build. <b>Use it at your own risk.</b> If any problems occured, please provide feedback on Github Issues.";
#else
    auto versionStr = qApp->applicationVersion();
#endif
    QMessageBox::about(this, tr("About"), tr(
                           R"(<h2>KiraOtoToolbox</h2>

<p>Copyright 2021 <a href="https://shine5402.top/about-me">shine_5402</a></p>
<p>Version %1</p>
<h3>About</h3>
<p>A toolbox for manipulating "oto.ini", the voicebank labeling format for UTAU.</p>
<h3>License</h3>
<p> This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.</p>
<p>This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.</p>
<p>You should have received a copy of the GNU General Public License
    along with this program.  If not, see <a href="https://www.gnu.org/licenses/">https://www.gnu.org/licenses/</a>.</p>

<h3>3rd party librarays used by this project</h3>
<ul>
<li>Qt, The Qt Company Ltd, under LGPL v3.</li>
<li>KiraUTAUUtils, shine_5402, under LGPL v3</li>
<li><a href="https://github.com/google/diff-match-patch">Diff-Match-Patch</a>, Copyright 2018 The diff-match-patch Authors, under the Apache License, Version 2.0</li>
<li><a href="https://github.com/Dobiasd/FunctionalPlus">FunctionalPlus</a>, BSL-1.0 License</li>
</ul>

<p>Some icons are provided by <a href="https://icons8.com">icons8</a>.</p>
)"
).arg(versionStr));
}

void MainWindow::showAboutQtDialog()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::showDonationPage()
{
    QDesktopServices::openUrl(QUrl{"https://afdian.net/@shine5402"});
}

void MainWindow::showUpdatePage()
{
    QDesktopServices::openUrl(QUrl{"https://github.com/shine5402/Shine5402OtoToolBox/releases"});
}

void MainWindow::showFeedbackPage()
{
    QDesktopServices::openUrl(QUrl{"https://github.com/shine5402/Shine5402OtoToolBox/issues"});
}

#ifndef NDEBUG
void MainWindow::debugFunction()
{

}
#endif
