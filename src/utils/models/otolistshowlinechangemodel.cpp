#include "otolistshowlinechangemodel.h"

OtoListShowLineChangeModel::OtoListShowLineChangeModel(const OtoEntryList* const oldEntryList, const OtoEntryList* const newEntryList, QObject *parent)
    : QAbstractTableModel(parent),
      oldEntryList(oldEntryList), newEntryList(newEntryList)
{
}

QVariant OtoListShowLineChangeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
            case OtoEntry::FILENAME: return tr("文件名");
            case OtoEntry::ALIAS: return tr("别名");
            case OtoEntry::LEFT: return tr("左");
            case OtoEntry::CONSONANT: return tr("固定范围");
            case OtoEntry::RIGHT: return tr("右");
            case OtoEntry::PREUTTERANCE: return tr("先行发声");
            case OtoEntry::OVERLAP: return ("重叠");
        }
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        return QString::number(section + 1);
    }
    return {};
}

int OtoListShowLineChangeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    //FIXME:
    //return std::max(oldEntryList->count(), newEntryList->count());
}

int OtoListShowLineChangeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return OtoEntry::OtoParameterCount;
}

QVariant OtoListShowLineChangeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

void OtoListShowLineChangeModel::generateResultList()
{
    resultList.clear();
    for (int i = 0; i < std::max(oldEntryList->count(), newEntryList->count()); ++i){
        
    }
}
