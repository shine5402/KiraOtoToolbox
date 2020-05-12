#include "otolistmodel.h"

OtoListModel::OtoListModel(OtoEntryList* entryList, QObject *parent)
    : QAbstractTableModel(parent), entryList(entryList)
{
}

QVariant OtoListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
            case FILENAME: return tr("文件名");
            case LEFT: return tr("左");
            case CONSONANT: return tr("固定范围");
            case RIGHT: return tr("右");
            case PREUTTERANCE: return tr("先行发声");
            case OVERLAP: return ("重叠");
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

    constexpr int parameterCount = 6;
    return parameterCount;
}

QVariant OtoListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (entryList)
        return {};

    if (role == Qt::DisplayRole)
    {
        auto oto = entryList->at(index.row());
        switch (index.column())
        {
            case FILENAME: return oto.fileName();
            case LEFT: return oto.left();
            case CONSONANT: return oto.consonant();
            case RIGHT: return oto.right();
            case PREUTTERANCE: return oto.preUtterance();
            case OVERLAP: return oto.overlap();
        }
    }

    return QVariant();
}
