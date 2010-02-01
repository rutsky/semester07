#include <QFileSystemModel>

#include "letterproxymodel.h"

LetterProxyModel::LetterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QVariant LetterProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        //return sourceFileSystemModel()->fileName(mapToSource(index));
        return QString("Index: (%1,%2)").arg(index.row()).arg(index.column());
    else
        return QVariant();
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
    QModelIndex const childIndex = sourceParent.child(sourceRow, 0);
    bool const isDir = sourceFileSystemModel()->isDir(childIndex);
    if (isDir)
        return rootPath().contains(sourceFileSystemModel()->filePath(childIndex), Qt::CaseSensitive);

    //return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    return true;
}

QFileSystemModel const * LetterProxyModel::sourceFileSystemModel() const
{
    return static_cast<QFileSystemModel const *>(sourceModel());
}
