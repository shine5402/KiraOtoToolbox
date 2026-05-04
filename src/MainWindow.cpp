#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QButtonGroup>
#include <QDesktopServices>
#include <QGroupBox>
#include "utils/dialogs/CommonHtmlDialog.h"
#include <QPushButton>
#include <QSettings>
#include <QUrl>

#include "addAffix/AddAffixDialogAdapter.h"
#include "overlapBatchSet/OverlapBatchSetDialogAdapter.h"
#include "removeAffix/RemoveAffixDialogAdapter.h"
#include "removeDuplicate/RemoveDuplicateDialogAdapter.h"
#include "toolBase/ToolDialog.h"
#include "toolBase/ToolManager.h"
#include "utils/UpdateChecker.h"
#include "utils/i18n/TranslationManager.h"
#include "utils/widgets/SvgWidget.h"

void MainWindow::setArgInfoBlock()
{
    auto args = qApp->arguments();

    if (args.count() < 2) {
        ui->argInfoBlock->hide();
    } else {
        args.removeFirst();
        ui->argInfoLabel->setText(tr("<p>It seems like that these filepaths provided in arguments. <br/>"
                                     "These paths will be used as tool's oto data input.</p><code><ul "
                                     "style='margin-left:15px;-qt-list-indent:0;'><li>%1</li></ul></code>")
                                      .arg(args.count() > 1 ? args.join("</li><li>") : args.at(0)));
    }
}

QMenu *MainWindow::createHelpMenu()
{
    auto helpMenu = new QMenu(tr("Help"), this);
    auto aboutAction = helpMenu->addAction(tr("About"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
    auto aboutQtAction = helpMenu->addAction(tr("About Qt"));
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    helpMenu->addSeparator();
    helpMenu->addAction(UpdateChecker::createAutoCheckAction());
    auto checkUpdateAction = helpMenu->addAction(tr("Check update now"));
    connect(checkUpdateAction, &QAction::triggered, this, [this]() { UpdateChecker::checkManually(updateChecker); });
    helpMenu->addSeparator();
    auto homepageAction = helpMenu->addAction(tr("Project homepage"));
    connect(homepageAction, &QAction::triggered, this,
            []() { QDesktopServices::openUrl(QUrl{"https://github.com/shine5402/KiraOtoToolbox"}); });

    return helpMenu;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // Replace the placeholder logoLabel with an SvgWidget that handles
    // HiDPI rendering and dark/light mode switching automatically.
    auto *logoWidget = new SvgWidget(QStringLiteral(":/logo/light"), QStringLiteral(":/logo/dark"), this);
    logoWidget->setFixedHeight(48);
    auto *logoLayout = qobject_cast<QHBoxLayout *>(ui->logoLabel->parentWidget()->layout());
    if (!logoLayout)
        logoLayout = qobject_cast<QHBoxLayout *>(ui->logoLabel->parent()->findChild<QHBoxLayout *>());
    if (logoLayout) {
        logoLayout->replaceWidget(ui->logoLabel, logoWidget);
    }
    ui->logoLabel->hide();

    setArgInfoBlock();

    // Create tool selector ui
    createToolSelectorUI();

    // create language menu
    ui->langButton->setMenu(TranslationManager::getManager()->getI18nMenu());

    // Help menu
    auto helpMenu = createHelpMenu();
    ui->helpButton->setMenu(helpMenu);

    // set window title
    setWindowTitle(tr("%1 ver.%2").arg(qApp->applicationName(), qApp->applicationVersion()));

    updateChecker = new UpdateChecker::GithubReleaseChecker("shine5402", "KiraOtoToolbox", this);
    UpdateChecker::triggerScheduledCheck(updateChecker);
}

void MainWindow::createToolSelectorUI()
{
    if (!toolButtonsLayoutResources.isEmpty()) {
        for (auto i : qAsConst(toolButtonsLayoutResources)) {
            auto widget = qobject_cast<QWidget *>(i);
            if (widget) {
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
    for (int groupID = 0; groupID < groups.count(); ++groupID) {
        auto group = groups.at(groupID);
        auto groupBox =
            new QGroupBox(group.isEmpty() ? tr("Uncategorized")
                                          : QCoreApplication::translate("TOOL_TYPE", group.toStdString().c_str()),
                          this);
        toolButtonsLayoutResources.append(groupBox);
        auto groupBoxLayout = new QVBoxLayout(groupBox);
        auto tools = toolGroups.values(group);
        std::reverse(tools.begin(), tools.end());
        for (const auto &tool : tools) {
            auto button = new QPushButton(tool.toolName(), groupBox);
            toolButtonGroup->addButton(button, availableTools.indexOf(tool));
            groupBoxLayout->addWidget(button);
        }
        ui->toolLayout->insertWidget(groupID, groupBox); // 1 stands for behind first spacer in ui layout
    }

    connect(toolButtonGroup, qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), toolButtonGroup,
            [toolButtonGroup, this](QAbstractButton *button) {
                auto tools = ToolManager::getManager()->getTools();
                auto dialog = new ToolDialog(tools.at(toolButtonGroup->id(button)).getAdapterInstance(this), nullptr);
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
    QString versionStr =
        tr("<p>Version %1, <i>build on %2 %3</i></p>")
            .arg(qApp->applicationVersion().isEmpty() ? "(unknown)" : qApp->applicationVersion(), __DATE__, __TIME__);

    auto dialog = new CommonHtmlDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("About"));
    dialog->setHTML(tr(
                        R"(<p style="text-align: left;"><img src=":/icon/appIcon" width="64"/></p>
<h2>KiraOtoToolbox</h2>
<p>Copyright 2021-present shine_5402</p>
%1
<h3>About</h3>
<p>A toolbox for manipulating "oto.ini", the voicebank labeling format for UTAU.</p>
<h3>License</h3>
<p> This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.<br>
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.<br>
You should have received a copy of the GNU General Public License
along with this program.  If not, see <a href="https://www.gnu.org/licenses/">https://www.gnu.org/licenses/</a>.<br>
</p>

<h3>Acknowledgements</h3>
<h4>Third-party libraries</h4>
<ul>
<li>Qt %2, The Qt Company Ltd, under LGPL v3.</li>
<li><a href="https://www.kfrlib.com/">KFR - Fast, modern C++ DSP framework</a>, under GNU GPL v2+</li>
<li><a href="https://github.com/cubicdaiya/dtl">dtl (Diff Template Library)</a>, Copyright (c) 2015 Tatsuhiko Kubo, under the BSD 3-Clause License</li>
<li><a href="https://github.com/Dobiasd/FunctionalPlus">FunctionalPlus</a>, BSL-1.0 License</li>
<li><a href="https://github.com/google/compact_enc_det">compact_enc_det</a>, Copyright 2016 Google Inc., under the Apache License, Version 2.0</li>
<li><a href="https://github.com/Waqar144/QSourceHighlite">QSourceHighlite</a>, Copyright (c) 2019-2020 Waqar Ahmed, under MIT License</li>
</ul>

<p>Some icons are provided by <a href="https://icons8.com">icons8</a>. JetBrains Mono font is included under the Apache License, Version 2.0.</p>
)")
                        .arg(versionStr, QT_VERSION_STR));
    dialog->setStandardButtons(QDialogButtonBox::Ok);
    dialog->setOpenExternalLinks(true);
    dialog->exec();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        createToolSelectorUI();
        setArgInfoBlock();
        ui->helpButton->menu()->deleteLater();
        ui->helpButton->setMenu(createHelpMenu());
    }
}
