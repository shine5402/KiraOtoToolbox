#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "removeduplicatedialog.h"
#include <QMessageBox>
#include "overlapsetdialog.h"
#include "addsuffixdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_duplicateRemoveButton_clicked()
{
    auto dialog = new RemoveDuplicateDialog(this);
    dialog->open();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("关于"), tr(R"(<h2>shine_5402 的 oto 工具箱</h2>

                                                <p>Copyright 2020 <a href="https://shine5402.top/about-me">shine_5402</a></p>
                                                <h3>关于</h3>
                                                <p>一个个人自用向的操作UTAU用声音资料库的原音设定文件oto.ini的工具箱</p>
                                                <h3>许可</h3>
                                                <p>本程序是自由软件：你可以在遵守由自由软件基金会发布的GNU通用公共许可证版本3（或者更新的版本）的情况下重新分发和/或修改本程序。</p>
                                                <p>本程序的发布旨在能够派上用场，但是<span style="font-weight: bold;">并不对此作出任何担保</span>；乃至也没有对<span style="font-weight: bold;">适销性</span>或<span style="font-weight: bold;">特定用途适用性</span>的默示担保。参见GNU通用公共许可证来获得更多细节。</p>
                                                <p>在得到本程序的同时，您应该也收到了一份GNU通用公共许可证的副本。如果没有，请查阅<a href="https://www.gnu.org/licenses/">https://www.gnu.org/licenses/</a>。</p>

                                                <h3>本程序使用的开源软件库</h3>
                                                <ul>
                                                <li>Qt, The Qt Company Ltd, under LGPL v3.</li>
                                                <li>Qt UTAU Librarys, shine_5402, under LGPL v3</li>
                                                </ul>
                                                )"));
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("关于 Qt"));
}

void MainWindow::on_overlapBatchSetButton_clicked()
{
    auto dialog = new OverlapSetDialog(this);
    dialog->open();
}

void MainWindow::on_suffixAddPushButton_clicked()
{
    auto dialog = new AddSuffixDialog(this);
    dialog->exec();
}
