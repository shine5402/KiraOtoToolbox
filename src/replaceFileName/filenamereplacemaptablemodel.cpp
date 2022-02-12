#include "filenamereplacemaptablemodel.h"

FileNameReplaceMapTableModel::FileNameReplaceMapTableModel(QHash<QString, QString> replaceMap, QObject *parent)
    : QAbstractTableModel(parent), replaceMap(replaceMap)
{
    keys = replaceMap.keys();
}

QVariant FileNameReplaceMapTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole){
        if (orientation == Qt::Orientation::Horizontal)
        {
            switch (section){
                case 0: return tr("Original file name");
                case 1: return tr("New file name");
                default: Q_UNREACHABLE();
            }
        }
        else
        {
            return section + 1;
        }
    }
    return {};
}

int FileNameReplaceMapTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return replaceMap.count();
}

int FileNameReplaceMapTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant FileNameReplaceMapTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){
        switch (index.column()){
            case 0: return keys.at(index.row());
            case 1: return replaceMap.value(keys.at(index.row()));
            default: Q_UNREACHABLE();
        }
    }
    return QVariant();
}
