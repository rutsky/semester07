#include <QFileSystemModel>

#include "letterproxymodel.h"

#include "letterobject.h"

LetterProxyModel::LetterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    columns_ << tr("From") << tr("Subject") << tr("Date") << tr("Received") << tr("Size");
}

QVariant LetterProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        QModelIndex const sourceIndex = mapToSource(index);
        QString const filePath = sourceFileSystemModel()->filePath(sourceIndex);
        QScopedPointer<LetterObject> letter(LetterObject::load(filePath));
        switch (index.column())
        {
        case 0:
            return letter->sender();
        case 1:
            return letter->subject();
        case 2:
            return letter->sentDate();
        case 3:
            return letter->receivedDate();
        case 4:
            return letter->size();
        default:
            Q_ASSERT(0);
            return QVariant();
        }

        //return sourceFileSystemModel()->fileName(mapToSource(index));
        //return QString("Index: (%1,%2)").arg(index.row()).arg(index.column());
    }
    else
        return QVariant();
}

QVariant LetterProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section < columns_.size())
        return columns_[section];
    else
        return QVariant();
}

int LetterProxyModel::columnCount(const QModelIndex &/* parent */) const
{
    return columns_.size();
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

    return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
}

QFileSystemModel const * LetterProxyModel::sourceFileSystemModel() const
{
    return static_cast<QFileSystemModel const *>(sourceModel());
}
