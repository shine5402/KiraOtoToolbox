#ifndef FILENAMEREPLACEMAPTABLEMODEL_H
#define FILENAMEREPLACEMAPTABLEMODEL_H

#include <QAbstractTableModel>

class FileNameReplaceMapTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    FileNameReplaceMapTableModel(QHash<QString, QString> replaceMap, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QHash<QString, QString> replaceMap;
    QStringList keys;//cache for performance
};

#endif // FILENAMEREPLACEMAPTABLEMODEL_H
