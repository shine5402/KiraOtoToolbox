#include "otofilemultipleloadotofilelistmodel.h"

OtoFileMultipleLoadOtoFileListModel::OtoFileMultipleLoadOtoFileListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant OtoFileMultipleLoadOtoFileListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList.at(section);
    }

    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        return QString::number(section + 1);
    }
    return {};
}

int OtoFileMultipleLoadOtoFileListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return datas.count();
}

int OtoFileMultipleLoadOtoFileListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant OtoFileMultipleLoadOtoFileListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){
        if (index.column() == Columns::FileName){
            return datas.at(index.row()).fileName;
        }
        if (index.column() == Columns::Count){
            return datas.at(index.row()).entryList.count();
        }
    }


    return QVariant();
}

void OtoFileMultipleLoadOtoFileListModel::addData(const QString& fileName, const OtoEntryList& entryList)
{
    datas.append(OtoFileInfo{fileName, entryList});
}

void OtoFileMultipleLoadOtoFileListModel::deleteData(int index)
{
    datas.removeAt(index);
}

