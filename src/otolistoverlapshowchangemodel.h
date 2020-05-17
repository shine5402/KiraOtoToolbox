#ifndef OTOLISTOVERLAPSHOWCHANGEMODEL_H
#define OTOLISTOVERLAPSHOWCHANGEMODEL_H

#include <QAbstractTableModel>
#include "otoentry.h"

class OtoListOverlapShowChangeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoListOverlapShowChangeModel(OtoEntryList* const entryList, QVector<double>* const newOverlapList, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    OtoEntryList* const entryList;
    QVector<double>* const newOverlapList;
    enum {FILENAME, ALIAS, LEFT, CONSONANT, RIGHT, PREUTTERANCE, OVERLAP, NEWOVERLAP};
};

#endif // OTOLISTOVERLAPSHOWCHANGEMODEL_H
