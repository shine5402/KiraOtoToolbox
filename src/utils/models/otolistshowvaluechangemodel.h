#ifndef OTOLISTSHOWCHANGEMODEL_H
#define OTOLISTSHOWCHANGEMODEL_H

#include <QAbstractTableModel>
#include <otoentry.h>

class OtoListShowValueChangeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoListShowValueChangeModel(OtoEntryList* oldEntryList, OtoEntryList* newEntryList,
                                         OtoEntry::OtoParameters changedParamters, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    OtoEntryList* oldEntryList;
    OtoEntryList* newEntryList;
    OtoEntry::OtoParameters changedParameters;
    QStringList headerList;
    void refreshHeaderList();
};

#endif // OTOLISTSHOWCHANGEMODEL_H
