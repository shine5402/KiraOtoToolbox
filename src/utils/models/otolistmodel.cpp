#include "otolistmodel.h"

OtoListModel::OtoListModel(const OtoEntryList* const entryList, QObject *parent)
    : QAbstractTableModel(parent), entryList(entryList)
{
}

QVariant OtoListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
            case OtoEntry::FILENAME: return tr("Filename");
            case OtoEntry::ALIAS: return tr("Alias");
            case OtoEntry::LEFT: return tr("Left");
            case OtoEntry::CONSONANT: return tr("Const field");
            case OtoEntry::RIGHT: return tr("Right");
            case OtoEntry::PREUTTERANCE: return tr("Preutterance");
            case OtoEntry::OVERLAP: return ("Overlap");
        }
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        return QString::number(section + 1);
    }
    return {};
}

int OtoListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (!entryList)
        return 0;

    return entryList->count();
}

int OtoListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return OtoEntry::OtoParameterCount;
}

QVariant OtoListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (!entryList)
        return {};

    if (role == Qt::DisplayRole)
    {
        auto oto = entryList->at(index.row());
        switch (index.column())
        {
            case OtoEntry::FILENAME: return oto.fileName();
            case OtoEntry::ALIAS: return oto.alias();
            case OtoEntry::LEFT: return oto.left();
            case OtoEntry::CONSONANT: return oto.consonant();
            case OtoEntry::RIGHT: return oto.right();
            case OtoEntry::PREUTTERANCE: return oto.preUtterance();
            case OtoEntry::OVERLAP: return oto.overlap();
        }
    }

    return QVariant();
}
