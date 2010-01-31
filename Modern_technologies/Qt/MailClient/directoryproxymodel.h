#ifndef DIRECTORYPROXYMODEL_H
#define DIRECTORYPROXYMODEL_H

#include <QSortFilterProxyModel>

class DirectoryProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit DirectoryProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // DIRECTORYPROXYMODEL_H
