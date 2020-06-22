#ifndef OTOLISTMODEL_H
#define OTOLISTMODEL_H

#include <QAbstractTableModel>
#include <otoentry.h>

class OtoListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoListModel(OtoEntryList* const entryList, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    OtoEntryList* const entryList;
};

#endif // OTOLISTMODEL_H
