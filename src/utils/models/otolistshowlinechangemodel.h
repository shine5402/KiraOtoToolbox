#ifndef OTOLISTSHOWLINECHANGEMODEL_H
#define OTOLISTSHOWLINECHANGEMODEL_H

#include <QAbstractTableModel>
#include <otoentry.h>

class OtoListShowLineChangeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoListShowLineChangeModel(const OtoEntryList* const oldEntryList, const OtoEntryList* const newEntryList,
                                        QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    const OtoEntryList* const oldEntryList;
    const OtoEntryList* const newEntryList;
    OtoEntryList resultList{};
    enum ModificationType{Add, Delete};
    QVector<ModificationType> modificationTypes{};

    void generateResultList();
};

#endif // OTOLISTSHOWLINECHANGEMODEL_H
