#include "otofilelistmodel.h"

OtoFileListModel::OtoFileListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant OtoFileListModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int OtoFileListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_datas.count();
}

int OtoFileListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant OtoFileListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){
        if (index.column() == Columns::FileName){
            return m_datas.at(index.row()).fileName;
        }
        if (index.column() == Columns::Count){
            return m_datas.at(index.row()).entryList.count();
        }
    }


    return QVariant();
}

OtoFileInfo OtoFileListModel::data(int index)
{
    return m_datas.at(index);
}

void OtoFileListModel::addData(const QString& fileName, const OtoEntryList& entryList)
{
    beginInsertRows(QModelIndex{}, rowCount(), rowCount());
    m_datas.append(OtoFileInfo{fileName, entryList});
    emit dataChanged();
    endInsertRows();
}

void OtoFileListModel::deleteData(int index)
{
    beginRemoveRows(QModelIndex{}, rowCount() - 1, rowCount() - 1);
    m_datas.removeAt(index);
    emit dataChanged();
    endRemoveRows();
}

void OtoFileListModel::reset()
{
    beginResetModel();
    m_datas.clear();
    emit dataChanged();
    endResetModel();
}

QVector<OtoFileInfo> OtoFileListModel::datas() const
{
    return m_datas;
}

