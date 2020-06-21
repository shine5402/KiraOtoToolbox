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

    ToolDialog* dialog = nullptr;
    RemoveDuplicateOptions* options = nullptr;

    void prepareTestDir();
    void prepareDialogAndLoadFile(const QString& fileName);
    void acceptDialog();
    void setToolOptionsWrapper(std::function<void()> optionFunc);
    QStringList getAliasListFromFile(const QString& fileName);

    void doTest(const QString& srcFileName, const QStringList& expectedAliasList, const QString& saveToFileName = {}, std::function<void()> toolOptionSetFunc = {}, const QString& saveDelTo = {}, const QStringList& saveDelToExpected = {});

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

void RemoveDuplicateTest::initTestCase()
{

}

void RemoveDuplicateTest::init()
{
    prepareTestDir();
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

void RemoveDuplicateTest::prepareDialogAndLoadFile(const QString& fileName)
{
    dialog = new ToolDialog(new RemoveDuplicateDialogAdapter(this));
    dialog->open();
    dialog->ui->otoLoadWidget->setFileName(testDir.filePath(fileName));
    QMetaObject::invokeMethod(dialog->ui->otoLoadWidget, "loadOtoFile");
    QVERIFY(dialog->ui->optionWidget->isEnabled());
}

void RemoveDuplicateTest::acceptDialog()
{
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
}

void RemoveDuplicateTest::setToolOptionsWrapper(std::function<void ()> optionFunc)
{
    if (optionFunc){
        options = new RemoveDuplicateOptions(this);
        optionFunc();
        qobject_cast<RemoveDuplicateDialogOptionWidget*>(dialog->ui->optionWidget)->setOptions(options);
    }
}

QStringList RemoveDuplicateTest::getAliasListFromFile(const QString& fileName)
{
    OtoFileReader reader(testDir.filePath(fileName));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    return aliasList;
}

void RemoveDuplicateTest::doTest(const QString& srcFileName, const QStringList& expectedAliasList, const QString& saveToFileName, std::function<void()> toolOptionSetFunc, const QString& saveDelTo, const QStringList& saveDelToExpected)
{
    prepareTestFile(":/file2Test/" + srcFileName);
    prepareDialogAndLoadFile(srcFileName);
    setToolOptionsWrapper(toolOptionSetFunc);
    if (!saveToFileName.isEmpty()){
        dialog->ui->otoSaveWidget->setSaveToCustom();
        dialog->ui->otoSaveWidget->setFileName(testDir.filePath(saveToFileName));
    }
    if (!saveDelTo.isEmpty()){
        dialog->ui->otoSaveWidget->setSecondFileNameUsed(true);
        dialog->ui->otoSaveWidget->setSecondFileName(testDir.filePath(saveDelTo));
    }
    acceptDialog();

    auto aliasList = getAliasListFromFile(saveToFileName.isEmpty() ? srcFileName : saveToFileName);
    qDebug() << aliasList << expectedAliasList;
    QCOMPARE(aliasList, expectedAliasList);
    if (!saveDelTo.isEmpty()){
        auto aliasList = getAliasListFromFile(saveDelTo);
        QCOMPARE(aliasList, saveDelToExpected);
    }
}

void RemoveDuplicateTest::cleanup()
{
    if (QTest::currentTestFailed())
        shouldCleanInEnd = false;
    else
        cleanCurrentTestFiles();

    if (dialog){
        dialog->close();
        dialog->deleteLater();
        dialog = nullptr;
    }
    if (options){
        options->deleteLater();
        options = nullptr;
    }
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

void RemoveDuplicateTest::removeDuplicate_test()
{
    doTest("normalData.ini", {"- さ","a さ","a R","さ","a s","a 息R","u ・"});
}

void RemoveDuplicateTest::removeDuplicate_saveToOtherFile_test()
{
    doTest("normalData.ini", {"- さ","a さ","a R","さ","a s","a 息R","u ・"}, "normalData2.ini");
}

void RemoveDuplicateTest::removeDuplicate_saveDeletedToOtherFile_test()
{
    doTest("normalData.ini", {"- さ","a さ","a R","さ","a s","a 息R","u ・"}, {}, {},
           "normalDataDel.ini", {"- さ2","- さ3","a さ2","a R2","さ2","a s2","a 息R2","u ・2"});
}

void RemoveDuplicateTest::removeDuplicateWithSpecificSuffix_test()
{
    doTest("withSpecificSuffixData.ini", {"- さPower","a さPower","a RPower","さPower","a sPower","a 息RPower","u ・Power"}, {},
           [&](){
        options->ignoreSpecificSuffix = true;
        options->suffixList = QStringList{"Power"};
    }
    );
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_test()
{
    doTest("withPitchSuffixData.ini", {"- さA#3","a さA#3","a RA#3","さA#3","a sA#3","a 息RA#3","u ・A#3"}, {},
           [&](){
        options->ignorePitchSuffix = true;
    });
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_caseMatch_test()
{
    doTest("withPitchSuffixData.ini", {"- さA#3","a さA#3","a RA#3","さA#3","a sA#3","a 息RA#3","u ・A#3"}, {},
           [&](){
                   options->ignorePitchSuffix = true;
                   options->pitchCaseSensitive = Qt::CaseSensitive;
                   options->pitchCase = OtoEntryFunctions::Upper;
               });
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_caseNotMatch_test()
{
    doTest("withPitchSuffixData.ini", getAliasListFromFile(":/file2Test/withPitchSuffixData.ini"), {}, [&](){
        options->ignorePitchSuffix = true;
        options->pitchCaseSensitive = Qt::CaseSensitive;
        options->pitchCase = OtoEntryFunctions::Lower;
    });
}

void RemoveDuplicateTest::organizeDuplicate_test()
{
    doTest("needOrganizedData.ini", {"- さ","- さ2","a さ"}, {}, [&](){
        options = new RemoveDuplicateOptions;
        options->shouldOrganize = true;
        options->maxDuplicateCount = 0;
    });
}

void RemoveDuplicateTest::organizeDuplicate_from1_test()
{
    doTest("needOrganizedData.ini", {"- さ","- さ1","a さ"}, {}, [&](){
        options->shouldOrganize = true;
        options->maxDuplicateCount = 0;
        options->organizeStartFrom1 = true;
    });
}

void RemoveDuplicateTest::organizeDuplicate_convertPitchCase()
{
    doTest("withPitchSuffixData.ini", {"- さa#3","a さa#3","a Ra#3","さa#3","a sa#3","a 息Ra#3","u ・a#3"},{},
           [&](){
                   options->ignorePitchSuffix = true;
                   options->shouldOrganize = true;
                   options->pitchCaseOrganized = OtoEntryFunctions::Lower;
                   options->maxDuplicateCount = 1;
               });
}

QTEST_MAIN(RemoveDuplicateTest)

#include "tst_removeduplicatetest.moc"
