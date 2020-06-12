#ifndef OTOLISTALIASSHOWCHANGEMODEL_H
#define OTOLISTALIASSHOWCHANGEMODEL_H

#include <QAbstractTableModel>
#include "otoentry.h"

class OtoListAliasShowChangeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OtoListAliasShowChangeModel(const OtoEntryList* const entryList, const QStringList* const newAliasList, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    const OtoEntryList* const entryList;
    const QStringList* const newAliasList;
    enum {FILENAME, ALIAS, NEWALIAS, LEFT, CONSONANT, RIGHT, PREUTTERANCE, OVERLAP};

};

#endif // OTOLISTALIASSHOWCHANGEMODEL_H
