#include <QFileSystemModel>

#include "letterproxymodel.h"

LetterProxyModel::LetterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QString LetterProxyModel::rootPath() const
{
    return rootPath_;
}

void LetterProxyModel::setRootPath(QString const &path)
{
    rootPath_ = path;
    invalidateFilter();
}

bool LetterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!sourceParent.isValid())
        return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    QFileSystemModel const *fileSystemModel = static_cast<QFileSystemModel const *>(sourceModel());
    QModelIndex const childIndex = sourceParent.child(sourceRow, 0);
    bool const isDir = fileSystemModel->isDir(childIndex);
    if (isDir)
        return rootPath().contains(fileSystemModel->filePath(childIndex), Qt::CaseSensitive);

    //return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    return true;
}
