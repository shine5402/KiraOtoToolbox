#include <QtTest>

#include <otoentry.h>
#include "toolBase/tooldialog.h"
#include <QTimer>
#include <QMessageBox>
#include "utils/dialogs/showotolistdialog.h"
#include "ui_tooldialog.h"
#include "otofilereader.h"
#include <QRandomGenerator>
#include <QPushButton>
#include "removeDuplicate/removeduplicatedialogoptionwidget.h"
#include "removeDuplicate/removeduplicatedialogadapter.h"

//为了NTFS权限处理
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

class RemoveDuplicateTest : public QObject
{
    Q_OBJECT

public:
    RemoveDuplicateTest();
    ~RemoveDuplicateTest();
private:
    void prepareTestFile(const QString& requiredFileName);
    void deleteTestFiles();
    QDir testDir;
    void cleanCurrentTestFiles();
    bool shouldCleanInEnd = true;

    void prepareTestDir();

private slots:
    void initTestCase();
    void init();
    void removeDuplicate_test();
    void removeDuplicate_saveToOtherFile_test();
    void removeDuplicate_saveDeletedToOtherFile_test();
    void removeDuplicateWithSpecificSuffix_test();
    void removeDuplicateWithPitchSuffix_test();
    void removeDuplicateWithPitchSuffix_caseMatch_test();
    void removeDuplicateWithPitchSuffix_caseNotMatch_test();
    void organizeDuplicate_test();
    void organizeDuplicate_from1_test();
    void organizeDuplicate_convertPitchCase();
    void cleanup();
};

RemoveDuplicateTest::RemoveDuplicateTest()
{

}

RemoveDuplicateTest::~RemoveDuplicateTest()
{

}

void RemoveDuplicateTest::prepareTestDir()
{
    QDir dir{};
    dir.makeAbsolute();
    QString testDirName{};
    do
    {
        testDirName = QString("test") + QString::number(QRandomGenerator::global()->bounded(1000));
    }
    while (QFileInfo::exists(dir.filePath(testDirName)));

    Q_ASSERT(dir.mkdir(testDirName));
    Q_ASSERT(dir.cd(testDirName));
    testDir = dir;
}

void RemoveDuplicateTest::prepareTestFile(const QString& requiredFileName)
{
    auto fileName = QFileInfo(requiredFileName).fileName();
    Q_ASSERT(QFile::copy(requiredFileName, testDir.filePath(fileName)));
    QFile file(testDir.filePath(fileName));
    //去除只读
    qt_ntfs_permission_lookup++;
    if (!file.permissions().testFlag(QFileDevice::WriteOther))
        file.setPermissions(file.permissions() | QFileDevice::WriteOther);
    qt_ntfs_permission_lookup--;
}

void RemoveDuplicateTest::cleanCurrentTestFiles()
{
    auto entrys = testDir.entryList(QDir::NoDotAndDotDot | QDir::Files);
    for (auto entry : entrys)
    {
        QFile file(testDir.filePath(entry));
        if (file.exists())
        {
            qt_ntfs_permission_lookup++;
            if (!file.permissions().testFlag(QFileDevice::WriteOther))
                file.setPermissions(file.permissions() | QFileDevice::WriteOther);
            Q_ASSERT(file.remove());
            qt_ntfs_permission_lookup--;
        }
    }
    auto testDirName = testDir.dirName();
    Q_ASSERT(testDir.cdUp());
    Q_ASSERT(testDir.rmdir(testDirName));

}

void RemoveDuplicateTest::initTestCase()
{

}

void RemoveDuplicateTest::init()
{
    prepareTestDir();
}

//TODO:Write test for load file widget
//void RemoveDuplicateTest::loadFile_test()
//{

//        auto dialog = new RemoveDuplicateDialog(new RemoveDuplicateDialogAdapter(this));
//    dialog->open();
//    dialog->ui->otoLoadWidget->setFileName(":/file2Test/normalData.ini");
//    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
//    QCOMPARE(dialog->entryList.count(), 15);
//    dialog->close();
//    dialog->deleteLater();
//}

void RemoveDuplicateTest::removeDuplicate_test()
{
    prepareTestFile(":/file2Test/normalData.ini");
    auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("normalData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("normalData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さ","a さ","a R","さ","a s","a 息R","u ・"};
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicate_saveToOtherFile_test()
{
    prepareTestFile(":/file2Test/normalData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("normalData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    dialog->ui->otoSaveWidget->setSaveToCustom();
    dialog->ui->otoSaveWidget->setFileName(testDir.filePath("normalData2.ini"));
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("normalData2.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さ","a さ","a R","さ","a s","a 息R","u ・"};
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicate_saveDeletedToOtherFile_test()
{
    prepareTestFile(":/file2Test/normalData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("normalData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    dialog->ui->otoSaveWidget->setSecondFileNameUsed(true);
    dialog->ui->otoSaveWidget->setSecondFileName(testDir.filePath("normalData2.ini"));
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("normalData2.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さ2","- さ3","a さ2","a R2","さ2","a s2","a 息R2","u ・2"};
    qDebug() << aliasList;
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicateWithSpecificSuffix_test()
{
    prepareTestFile(":/file2Test/withSpecificSuffixData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("withSpecificSuffixData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    //因为直接发送点击事件会点击在QCheckBox的中心而导致无法选中，因为Qt本身应当是提供点击 -> Checked的保证的，此处直接设置Checked，而不是指定位置点击
    //    dialog->ui->ignoreSpecificSuffixCheckBox->setChecked(true);
    //    QVERIFY(dialog->ui->suffixListWidget->isEnabled());
    //    dialog->ui->suffixListWidget->setData({"Power"});
    auto options = new RemoveDuplicateOptions(this);
    options->ignoreSpecificSuffix = true;
    options->suffixList = QStringList{"Power"};
    qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);

    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withSpecificSuffixData.ini"));
    auto list = reader.getEntryList();
    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さPower","a さPower","a RPower","さPower","a sPower","a 息RPower","u ・Power"};
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_test()
{
    prepareTestFile(":/file2Test/withPitchSuffixData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("withPitchSuffixData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    //    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    //    QVERIFY(dialog->ui->widget->isEnabled());
    auto options = new RemoveDuplicateOptions;
    options->ignorePitchSuffix = true;
    qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);

    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();
    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さA#3","a さA#3","a RA#3","さA#3","a sA#3","a 息RA#3","u ・A#3"};
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_caseMatch_test()
{
    prepareTestFile(":/file2Test/withPitchSuffixData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("withPitchSuffixData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    //    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    //    dialog->ui->caseSensitiveCheckBox->setChecked(true);
    //    dialog->ui->caseComboBox->setCurrentIndex(0);
    auto options = new RemoveDuplicateOptions;
    options->ignorePitchSuffix = true;
    options->pitchCaseSensitive = Qt::CaseSensitive;
    options->pitchCase = OtoEntryFunctions::Upper;
    qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);

    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();
    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さA#3","a さA#3","a RA#3","さA#3","a sA#3","a 息RA#3","u ・A#3"};
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_caseNotMatch_test()
{
    prepareTestFile(":/file2Test/withPitchSuffixData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("withPitchSuffixData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    //    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    //    dialog->ui->caseSensitiveCheckBox->setChecked(true);
    //    dialog->ui->caseComboBox->setCurrentIndex(1);
    auto options = new RemoveDuplicateOptions;
    options->ignorePitchSuffix = true;
    options->pitchCaseSensitive = Qt::CaseSensitive;
    options->pitchCase = OtoEntryFunctions::Lower;
    qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();
    QCOMPARE(list.count(), 15);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::organizeDuplicate_test()
{
    prepareTestFile(":/file2Test/needOrganizedData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("needOrganizedData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    //    dialog->ui->organizeCheckBox->setChecked(true);
    //    dialog->ui->maxSpinBox->setValue(0);
    auto options = new RemoveDuplicateOptions;
    options->shouldOrganize = true;
    options->maxDuplicateCount = 0;
    qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("needOrganizedData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さ","- さ2","a さ"};
    //QCOMPARE(list.count(), expectedAliasList.count());
    //QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::organizeDuplicate_from1_test()
{
    prepareTestFile(":/file2Test/needOrganizedData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("needOrganizedData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    //    dialog->ui->organizeCheckBox->setChecked(true);
    //    dialog->ui->maxSpinBox->setValue(0);
    //    dialog->ui->organizeStartFrom1CheckBox->setChecked(true);
    auto options = new RemoveDuplicateOptions;
    options->shouldOrganize = true;
    options->maxDuplicateCount = 0;
    options->organizeStartFrom1 = true;
    qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("needOrganizedData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さ","- さ1","a さ"};
    //QCOMPARE(list.count(), expectedAliasList.count());
    //QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::organizeDuplicate_convertPitchCase()
{
    prepareTestFile(":/file2Test/withPitchSuffixData.ini");
        auto dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath("withPitchSuffixData.ini"));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    //    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    //    QVERIFY(dialog->ui->widget->isEnabled());
    //    dialog->ui->organizeCheckBox->setChecked(true);
    //    dialog->ui->organizeCaseComboBox->setCurrentIndex(1);
    //    dialog->ui->maxSpinBox->setValue(1);
    auto options = new RemoveDuplicateOptions;
    options->ignorePitchSuffix = true;
    options->shouldOrganize = true;
    options->pitchCaseOrganized = OtoEntryFunctions::Lower;
    options->maxDuplicateCount = 1;
    qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さa#3","a さa#3","a Ra#3","さa#3","a sa#3","a 息Ra#3","u ・a#3"};
    //QCOMPARE(list.count(), expectedAliasList.count());
    //QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    QCOMPARE(aliasList, expectedAliasList);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::cleanup()
{
    if (QTest::currentTestFailed())
        shouldCleanInEnd = false;
    else
        cleanCurrentTestFiles();
}

QTEST_MAIN(RemoveDuplicateTest)

#include "tst_removeduplicatetest.moc"
