#include <QtTest>
#include <utils/widgets/otofilenameeditwithbrowse.h>
#include "utils/widgets/filenameeditwithbrowse.h"
#include "utils/widgets/otofileloadwidget.h"
#include "utils/widgets/otofilesavewidget.h"
#include "utils/widgets/stringlistmodifywidget.h"
#include "ui_filenameeditwithbrowse.h"
#include "ui_otofileloadwidget.h"
#include "ui_otofilesavewidget.h"
#include "ui_stringlistmodifywidget.h"
// add necessary includes here

class UtilWidgetsTest : public QObject
{
    Q_OBJECT

public:
    UtilWidgetsTest();
    ~UtilWidgetsTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void FileNameEditWithBrowseTest();
    void OtoFileNameEditWithBrowseTest();
    void OtoFileLoadWidgetTest();
    void OtoFileSaveWidgetTest();
    void StringModifyWidgetTest();
};

UtilWidgetsTest::UtilWidgetsTest()
{

}

UtilWidgetsTest::~UtilWidgetsTest()
{

}

void UtilWidgetsTest::initTestCase()
{

}

void UtilWidgetsTest::cleanupTestCase()
{

}

void UtilWidgetsTest::FileNameEditWithBrowseTest()
{
    auto edit = new FileNameEditWithBrowse();
    QString* selectedFilter = new QString();
    edit->setParameters("testCaption", "testDir", "testFilter", selectedFilter, QFileDialog::Option::DontConfirmOverwrite);
    QCOMPARE(edit->getCaption(), "testCaption");
    QCOMPARE(edit->getDir(), "testDir");
    QCOMPARE(edit->getFilter(), "testFilter");
    QCOMPARE(edit->getSelectedFilter(), selectedFilter);
    QCOMPARE(edit->getOptions(), QFileDialog::Option::DontConfirmOverwrite);
    edit->setFileName(":/test");
    QCOMPARE(edit->ui->fileNameEdit->text(), ":/test");
    edit->deleteLater();
    delete selectedFilter;

    auto editOpen = new FileNameEditWithOpenBrowse();
    QVERIFY(editOpen->getPurpose() == FileNameEditWithBrowse::Open);
    QTest::mouseClick(editOpen->ui->browseButton,Qt::LeftButton);
    QCOMPARE(editOpen->fileName(), ":/testOpen");
    editOpen->deleteLater();

    auto editSave = new FileNameEditWithSaveBrowse();
    QVERIFY(editSave->getPurpose() == FileNameEditWithBrowse::Save);
    QTest::mouseClick(editSave->ui->browseButton,Qt::LeftButton);
    QCOMPARE(editSave->fileName(), ":/testSave");
    editSave->deleteLater();
}

void UtilWidgetsTest::OtoFileNameEditWithBrowseTest()
{
    auto editOpen = new OtoFileNameEditWithOpenBrowse();
    QCOMPARE(editOpen->getCaption(), editOpen->tr("选择一个原音设定文件"));
    QCOMPARE(editOpen->getFilter(), editOpen->tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    editOpen->deleteLater();

    auto editSave = new OtoFileNameEditWithSaveBrowse();
    QCOMPARE(editSave->getCaption(), editSave->tr("指定保存路径"));
    QCOMPARE(editSave->getFilter(), editSave->tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    editSave->deleteLater();
}

void UtilWidgetsTest::OtoFileLoadWidgetTest()
{
    auto loadWidget = new OtoFileLoadWidget();
    loadWidget->setFileName(":/file2Test/testLoad.ini");
    QSignalSpy spy(loadWidget, &OtoFileLoadWidget::loaded);
    QTest::mouseClick(loadWidget->ui->loadButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QVERIFY(loadWidget->isEntryListReaded());
    auto otoList = loadWidget->getEntryList();
    const auto otoListExpected = OtoEntryList {
    {"_さんささすぃさすさ.wav","- さ",1,2,3,4,5},
    {"_さんささすぃさすさ.wav","a さ",1,2,3,4,5},};
    QCOMPARE(otoList, otoListExpected);

    QVERIFY(!connect(loadWidget->ui->showOtoListButton, &QPushButton::clicked, loadWidget, &OtoFileLoadWidget::showOtoListDialog, Qt::UniqueConnection));
    QTest::mouseClick(loadWidget->ui->showOtoListButton, Qt::LeftButton);


    loadWidget->deleteLater();
}

void UtilWidgetsTest::OtoFileSaveWidgetTest()
{
    auto saveWidget = new OtoFileSaveWidget();
    saveWidget->show();
    QVERIFY(!saveWidget->isEnabled());
    saveWidget->setEnabled(true);

    saveWidget->setSaveToSrc();
    QVERIFY(saveWidget->isSaveToSrc());
    QVERIFY(!saveWidget->isSaveToCustom());

    saveWidget->setSaveToCustom();
    QVERIFY(!saveWidget->isSaveToSrc());
    QVERIFY(saveWidget->isSaveToCustom());

    QTest::mouseClick(saveWidget->ui->saveToSrcRadioButton, Qt::LeftButton);
    QVERIFY(saveWidget->isSaveToSrc());
    QVERIFY(!saveWidget->isSaveToCustom());

    QTest::mouseClick(saveWidget->ui->saveToCustomRadioButton, Qt::LeftButton);
    QVERIFY(!saveWidget->isSaveToSrc());

    saveWidget->setFileName(":/testCustom");
    QCOMPARE(saveWidget->fileName(), ":/testCustom");

    saveWidget->setSecondFileNameAvailable(true);
    QVERIFY(saveWidget->isSecondFileNameAvailable());
    QVERIFY(saveWidget->ui->secondFileNameWidget->isVisible());
    QVERIFY(!saveWidget->ui->secondFileNameEdit->isEnabled());
    QTest::mouseClick(saveWidget->ui->secondFileNameCheckBox, Qt::LeftButton);
    QVERIFY(saveWidget->ui->secondFileNameEdit->isEnabled());
    QVERIFY(saveWidget->isSecondFileNameAvailable());
    saveWidget->setSecondFileNameCheckBoxText("testSecondCheckBoxText");
    QCOMPARE(saveWidget->ui->secondFileNameCheckBox->text(), "testSecondCheckBoxText");
    saveWidget->setSecondFileName(":/testSecond");
    QCOMPARE(saveWidget->secondFileName(), ":/testSecond");
    QCOMPARE(saveWidget->ui->secondFileNameEdit->fileName(), ":/testSecond");
    saveWidget->deleteLater();
}

void UtilWidgetsTest::StringModifyWidgetTest()
{
    auto widget = new StringListModifyWidget;
    QVERIFY(!connect(widget->ui->addButton, &QPushButton::clicked, widget, &StringListModifyWidget::addRow, Qt::UniqueConnection));
    QVERIFY(!connect(widget->ui->deleteButton, &QPushButton::clicked, widget, &StringListModifyWidget::deleteCurrentRow, Qt::UniqueConnection));

    QTest::mouseClick(widget->ui->addButton, Qt::LeftButton);
    QCOMPARE(widget->getData(), {{"TestAdd"}});
    widget->ui->listView->setCurrentIndex(widget->ui->listView->model()->index(0,0));
    QTest::mouseClick(widget->ui->deleteButton, Qt::LeftButton);
    QCOMPARE(widget->getData(), {});
}



QTEST_MAIN(UtilWidgetsTest)

#include "tst_utilwidgetstest.moc"
