#include <QFileSystemModel>

#include "directoryproxymodel.h"

DirectoryProxyModel::DirectoryProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool DirectoryProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!sourceParent.isValid())
        return false;
    QFileSystemModel const *sourceModel = static_cast<QFileSystemModel const *>(sourceParent.model());
    return sourceModel->isDir(sourceParent.child(sourceRow, 0));
}
