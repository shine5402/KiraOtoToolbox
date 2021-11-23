#ifndef OTOFILEMULTIPLELOADOTOFILELISTMODEL_H
#define OTOFILEMULTIPLELOADOTOFILELISTMODEL_H

#include <QAbstractTableModel>
#include <OtoUtil/otoentry.h>

struct OtoFileInfo{
    QString fileName;
    OtoEntryList entryList;
};

class OtoFileListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoFileListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    OtoFileInfo data(int index);

    void addData(const QString& fileName, const OtoEntryList& entryList);
    void deleteData(int index);

    void reset();
    QVector<OtoFileInfo> datas() const;

private:
    QVector<OtoFileInfo> m_datas;
    const QStringList headerList = {tr("路径"), tr("oto 条目数")};
    enum Columns{FileName, Count};
signals:
    void dataChanged();
};

#endif // OTOFILEMULTIPLELOADOTOFILELISTMODEL_H
