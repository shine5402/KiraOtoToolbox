#ifndef OTOFILEMULTIPLELOADOTOFILELISTMODEL_H
#define OTOFILEMULTIPLELOADOTOFILELISTMODEL_H

#include <QAbstractTableModel>
#include <otoentry.h>

struct OtoFileInfo{
    QString fileName;
    OtoEntryList entryList;
};

class OtoFileMultipleLoadOtoFileListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoFileMultipleLoadOtoFileListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addData(const QString& fileName, const OtoEntryList& entryList);
    void deleteData(int index);

private:
    QVector<OtoFileInfo> datas;
    const QStringList headerList = {tr("路径"), tr("oto 条目数")};
    enum Columns{FileName, Count};
};

#endif // OTOFILEMULTIPLELOADOTOFILELISTMODEL_H
