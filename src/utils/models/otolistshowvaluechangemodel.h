#ifndef OTOLISTSHOWCHANGEMODEL_H
#define OTOLISTSHOWCHANGEMODEL_H

#include <QAbstractTableModel>
#include <otoentry.h>

class OtoListShowValueChangeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    OtoListShowValueChangeModel(const OtoEntryList* const oldEntryList, const OtoEntryList* const newEntryList,
                                         OtoEntry::OtoParameters changedParamters, int precision = OTOENTRY_DEFAULT_PRECISION, QObject *parent = nullptr);
    OtoListShowValueChangeModel(const OtoEntryList* const oldEntryList, const OtoEntryList* const newEntryList, int precision = OTOENTRY_DEFAULT_PRECISION, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    static OtoEntry::OtoParameters guessChangedParameters(const OtoEntryList& oldEntryList, const OtoEntryList newEntryList);

private:
    const OtoEntryList* const oldEntryList;
    const OtoEntryList* const newEntryList;
    OtoEntry::OtoParameters changedParameters;
    QStringList headerList;
    void refreshHeaderList();
    void construct(const OtoEntryList* const oldEntryList, const OtoEntryList* const newEntryList);
    int precision;
};

#endif // OTOLISTSHOWCHANGEMODEL_H
