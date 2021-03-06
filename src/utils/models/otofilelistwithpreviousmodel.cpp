#include "otofilelistwithpreviousmodel.h"

OtoFileListWithPreviousModel::OtoFileListWithPreviousModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant OtoFileListWithPreviousModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int OtoFileListWithPreviousModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_datas.count();
}

int OtoFileListWithPreviousModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant OtoFileListWithPreviousModel::data(const QModelIndex &index, int role) const
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
        if (index.column() == Columns::PreCount){
            return m_datas.at(index.row()).previousEntryList.count();
        }
    }


    return QVariant();
}

QVector<OtoFileInfoWithPrevious> OtoFileListWithPreviousModel::datas() const
{
    return m_datas;
}

void OtoFileListWithPreviousModel::setDatas(const QVector<OtoFileInfoWithPrevious>& datas)
{
    m_datas = datas;
}

void OtoFileListWithPreviousModel::addData(const QString& fileName, const OtoEntryList& entryList, const OtoEntryList& previousEntryList)
{
    beginInsertRows(QModelIndex{}, rowCount(), rowCount());
    m_datas.append(OtoFileInfoWithPrevious{fileName, entryList, previousEntryList});
    endInsertRows();
}

void OtoFileListWithPreviousModel::deleteData(int index)
{
    beginRemoveRows(QModelIndex{}, rowCount() - 1, rowCount() - 1);
    m_datas.removeAt(index);
    endRemoveRows();
}

void OtoFileListWithPreviousModel::reset()
{
    beginResetModel();
    m_datas.clear();
    endResetModel();
}
