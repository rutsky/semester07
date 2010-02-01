#include <QFileSystemModel>

#include "directoryproxymodel.h"

DirectoryProxyModel::DirectoryProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool DirectoryProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!sourceParent.isValid())
        return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    QFileSystemModel const *fileSystenModel = static_cast<QFileSystemModel const *>(sourceModel());
    return fileSystenModel->isDir(sourceParent.child(sourceRow, 0));
}
