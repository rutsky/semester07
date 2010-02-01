#include <QFileSystemModel>

#include "letterproxymodel.h"

LetterProxyModel::LetterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool LetterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!sourceParent.isValid())
        return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    QFileSystemModel const *fileSystemModel = static_cast<QFileSystemModel const *>(sourceModel());
    QModelIndex const childIndex = sourceParent.child(sourceRow, 0);
    bool const isDir = fileSystemModel->isDir(childIndex);
    if (isDir)
        return fileSystemModel->rootPath().contains(fileSystemModel->filePath(childIndex), Qt::CaseSensitive);

    return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
}
