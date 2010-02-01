#ifndef LETTERPROXYMODEL_H
#define LETTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class LetterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit LetterProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // LETTERPROXYMODEL_H
