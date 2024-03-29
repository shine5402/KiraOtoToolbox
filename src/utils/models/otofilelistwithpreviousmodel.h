#ifndef OTOFILELISTDIFFMODEL_H
#define OTOFILELISTDIFFMODEL_H

#include <QAbstractTableModel>
#include <OtoUtil/otoentry.h>

struct OtoFileInfoWithPrevious{
    QString fileName;
    OtoEntryList entryList;
    OtoEntryList previousEntryList;
};

class OtoFileListWithPreviousModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoFileListWithPreviousModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVector<OtoFileInfoWithPrevious> datas() const;
    void setDatas(const QVector<OtoFileInfoWithPrevious>& datas);

    void addData(const QString& fileName, const OtoEntryList& entryList, const OtoEntryList& previousEntryList);
    void deleteData(int index);
    void reset();

private:
    QVector<OtoFileInfoWithPrevious> m_datas;
    const QStringList headerList = {tr("Path"), tr("Current oto entry count"), tr("Previous oto entry count")};
    enum Columns{FileName, Count, PreCount};
};

#endif // OTOFILELISTDIFFMODEL_H
