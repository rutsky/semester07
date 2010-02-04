#include <QFileSystemModel>
#include <QVariant>
#include <QDebug>

#include "letterproxymodel.h"

#include "letterobject.h"

LetterProxyModel::LetterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    //columns_ << tr("From") << tr("Subject") << tr("Date") << tr("Received") << tr("Size");
    columns_ << tr("From") << tr("Subject") << tr("Received") << tr("Size");
}

QVariant LetterProxyModel::dataFromSource(const QModelIndex &sourceIndex, int role) const
{
    if (!sourceIndex.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        QString const filePath = sourceFileSystemModel()->filePath(sourceIndex);
        QScopedPointer<LetterObject> letter(LetterObject::load(filePath));
        /*
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
        */
        switch (sourceIndex.column())
        {
        case 0:
            return letter->sender();
        case 1:
            return letter->subject();
        case 2:
            return letter->receivedDate();
        case 3:
            return letter->size();
        default:
            Q_ASSERT(0);
            return QVariant();
        }
    }
    else
        return QVariant();
}

QVariant LetterProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QModelIndex const sourceIndex = mapToSource(index);
    return dataFromSource(sourceIndex, role);
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

void LetterProxyModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << "sort";
    QSortFilterProxyModel::sort(column, order);
}

bool LetterProxyModel::lessThan(const QModelIndex &left,
                                const QModelIndex &right) const
{
    if (!left.isValid() || !right.isValid())
        return false;

    QVariant const leftData = dataFromSource(left, (int)Qt::DisplayRole);
    QVariant const rightData = dataFromSource(right, (int)Qt::DisplayRole);

    if (leftData.type() == QVariant::DateTime)
        return leftData.toDateTime() < rightData.toDateTime();
    else if (leftData.type() == QVariant::Int)
        return leftData.toInt() < rightData.toInt();
    else
        return leftData.toString() < rightData.toString();
}
