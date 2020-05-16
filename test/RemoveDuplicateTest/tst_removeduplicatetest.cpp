#include <QtTest>

#include <otoentry.h>
#include "../../src/removeduplicatedialog.h"
#include <QTimer>
#include <QMessageBox>
#include "../../src/showotolistdialog.h"
#include "ui_removeduplicatedialog.h"
#include "otofilereader.h"
#include <QRandomGenerator>

//为了NTFS权限处理
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

class RemoveDuplicateTest : public QObject
{
    Q_OBJECT

public:
    RemoveDuplicateTest();
    ~RemoveDuplicateTest();
private:
    void prepareTestFiles();
    void deleteTestFiles();
    QDir testDir;
    void cleanTestFiles();
    bool shouldCleanInEnd = true;

private slots:
    void initTestCase();
    void init();
    void loadFile_test();
    void removeDuplicate_test();
    void removeDuplicateWithSpecificSuffix_test();
    void specificSuffixList_test();
    void removeDuplicateWithPitchSuffix_test();
    void removeDuplicateWithPitchSuffix_caseMatch_test();
    void removeDuplicateWithPitchSuffix_caseNotMatch_test();
    void organizeDuplicate_test();
    void organizeDuplicate_from1_test();
    void organizeDuplicate_convertPitchCase();
    void cleanup();
};

static auto getIntersection = [] (QList<QList<QString> > lists) -> QList<QString> {
    QHash<QString,int> counts;
    QList<QString> result;
    for (auto list : lists)
    {
        for (auto i : list)
        {
            counts.insert(i,counts.value(i) + 1);
        }
    }
    for (auto it = counts.begin();it != counts.end();++it)
    {
        if (it.value() == lists.count())
            result.append(it.key());
    }
    return result;
};


RemoveDuplicateTest::RemoveDuplicateTest()
{

}

RemoveDuplicateTest::~RemoveDuplicateTest()
{
    if (shouldCleanInEnd)
        cleanTestFiles();
}

void RemoveDuplicateTest::prepareTestFiles()
{
    QDir dir{};
    dir.makeAbsolute();
    //auto testDirName = QString("test") + QString::number(QRandomGenerator::global()->bounded(1000));
    Q_ASSERT(dir.mkdir("test"));
    Q_ASSERT(dir.cd("test"));
    testDir = dir;

    const QStringList dataResList = {":/file2Test/normalData.ini", ":/file2Test/withPitchSuffixData.ini",
                                     ":/file2Test/withSpecificSuffixData.ini",":/file2Test/needOrganizedData.ini"};
    for (auto res : dataResList)
    {
        auto fileName = QFileInfo(res).fileName();
        Q_ASSERT(QFile::copy(res, dir.filePath(fileName)));
        QFile file(dir.filePath(fileName));
        //去除只读
        qt_ntfs_permission_lookup++;
        if (!file.permissions().testFlag(QFileDevice::WriteOther))
            file.setPermissions(file.permissions() | QFileDevice::WriteOther);
        qt_ntfs_permission_lookup--;
    }
}

void RemoveDuplicateTest::cleanTestFiles()
{
    QDir dir{};
    dir.makeAbsolute();
    if (dir.exists("test"))
    {
        Q_ASSERT(dir.cd("test"));
        auto entrys = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
        for (auto entry : entrys)
        {
            QFile file(dir.filePath(entry));
            if (file.exists())
            {
                qt_ntfs_permission_lookup++;
                if (!file.permissions().testFlag(QFileDevice::WriteOther))
                    file.setPermissions(file.permissions() | QFileDevice::WriteOther);
                Q_ASSERT(file.remove());
                qt_ntfs_permission_lookup--;
            }
        }
        Q_ASSERT(dir.cdUp());
        Q_ASSERT(dir.rmdir("test"));
    }
}

void RemoveDuplicateTest::initTestCase()
{
    //清理test临时文件夹
    cleanTestFiles();
}

void RemoveDuplicateTest::init()
{
    prepareTestFiles();
}

void RemoveDuplicateTest::loadFile_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(":/file2Test/normalData.ini");
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    QCOMPARE(dialog->entryList.count(), 15);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicate_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("normalData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("normalData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    //normalData:{"- さ","- さ2","- さ3","a さ","a さ2","a R","a R2","さ","さ2","a s","a s2","a 息R","a 息R2","u ・","u ・2"}
    const QStringList expectedAliasList = {"- さ","a さ","a R","さ","a s","a 息R","u ・"};
    QCOMPARE(list.count(), expectedAliasList.count());
    QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicateWithSpecificSuffix_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("withSpecificSuffixData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    //因为直接发送点击事件会点击在QCheckBox的中心而导致无法选中，因为Qt本身应当是提供点击 -> Checked的保证的，此处直接设置Checked，而不是指定位置点击
    dialog->ui->ignoreSpecificSuffixCheckBox->setChecked(true);
    QVERIFY(dialog->ui->suffixListWidget->isEnabled());
    //点击添加的测试略微有些麻烦，不过之后应该也能实现……这里就先放着吧
    dialog->ui->suffixListWidget->addItem("Power");
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withSpecificSuffixData.ini"));
    auto list = reader.getEntryList();
    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さPower","a さPower","a RPower","さPower","a sPower","a 息RPower","u ・Power"};
    QCOMPARE(list.count(), expectedAliasList.count());
    QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::specificSuffixList_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("withSpecificSuffixData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    dialog->ui->ignoreSpecificSuffixCheckBox->setChecked(true);
    QVERIFY(dialog->ui->suffixListWidget->isEnabled());
    QTest::mouseClick(dialog->ui->addSuffixButton, Qt::LeftButton);
    QVERIFY(dialog->ui->suffixListWidget->item(0));
    QCOMPARE(dialog->ui->suffixListWidget->item(0)->text(), "TestAdd");
    dialog->ui->suffixListWidget->selectionModel()->select(dialog->ui->suffixListWidget->model()->index(0,0),QItemSelectionModel::Select);
    QTest::mouseClick(dialog->ui->modifySuffixButton, Qt::LeftButton);
    QCOMPARE(dialog->ui->suffixListWidget->item(0)->text(), "TestModify");
    QTest::mouseClick(dialog->ui->deleteSuffixButton, Qt::LeftButton);
    QCOMPARE(dialog->ui->suffixListWidget->count(), 0);
    dialog->close();
    dialog->deleteLater();

}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("withPitchSuffixData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    QVERIFY(dialog->ui->widget->isEnabled());
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();
    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さA#3","a さA#3","a RA#3","さA#3","a sA#3","a 息RA#3","u ・A#3"};
    QCOMPARE(list.count(), expectedAliasList.count());
    QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_caseMatch_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("withPitchSuffixData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    dialog->ui->caseSensitiveCheckBox->setChecked(true);
    dialog->ui->caseComboBox->setCurrentIndex(0);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();
    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さA#3","a さA#3","a RA#3","さA#3","a sA#3","a 息RA#3","u ・A#3"};
    QCOMPARE(list.count(), expectedAliasList.count());
    QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::removeDuplicateWithPitchSuffix_caseNotMatch_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("withPitchSuffixData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    dialog->ui->caseSensitiveCheckBox->setChecked(true);
    dialog->ui->caseComboBox->setCurrentIndex(1);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);
    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();
    QCOMPARE(list.count(), 15);
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::organizeDuplicate_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("needOrganizedData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    dialog->ui->organizeCheckBox->setChecked(true);
    dialog->ui->maxSpinBox->setValue(0);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("needOrganizedData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さ","- さ2","a さ"};
    QCOMPARE(list.count(), expectedAliasList.count());
    QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::organizeDuplicate_from1_test()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("needOrganizedData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    dialog->ui->organizeCheckBox->setChecked(true);
    dialog->ui->maxSpinBox->setValue(0);
    dialog->ui->organizeStartFrom1CheckBox->setChecked(true);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("needOrganizedData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
    const QStringList expectedAliasList = {"- さ","- さ1","a さ"};
    QCOMPARE(list.count(), expectedAliasList.count());
    QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::organizeDuplicate_convertPitchCase()
{
    auto dialog = new RemoveDuplicateDialog();
    dialog->open();
    dialog->ui->fileNameEdit_open->setText(testDir.filePath("withPitchSuffixData.ini"));
    QTest::mouseClick(dialog->ui->loadButton, Qt::MouseButton::LeftButton);
    dialog->ui->ignorePitchSuffixCheckBox->setChecked(true);
    QVERIFY(dialog->ui->widget->isEnabled());
    dialog->ui->organizeCheckBox->setChecked(true);
    dialog->ui->organizeCaseComboBox->setCurrentIndex(1);
    dialog->ui->maxSpinBox->setValue(1);
    QTest::mouseClick(dialog->ui->buttonBox->button(QDialogButtonBox::Ok), Qt::MouseButton::LeftButton);

    OtoFileReader reader(testDir.filePath("withPitchSuffixData.ini"));
    auto list = reader.getEntryList();

    QStringList aliasList;
    for (auto i : list)
    {
        aliasList.append(i.alias());
    }
        const QStringList expectedAliasList = {"- さa#3","a さa#3","a Ra#3","さa#3","a sa#3","a 息Ra#3","u ・a#3"};
    QCOMPARE(list.count(), expectedAliasList.count());
    QCOMPARE(getIntersection({expectedAliasList, aliasList}).count(), expectedAliasList.count());
    dialog->close();
    dialog->deleteLater();
}

void RemoveDuplicateTest::cleanup()
{
    if (QTest::currentTestFailed())
        shouldCleanInEnd = false;
    else
        cleanTestFiles();
}

QTEST_MAIN(RemoveDuplicateTest)

#include "tst_removeduplicatetest.moc"
