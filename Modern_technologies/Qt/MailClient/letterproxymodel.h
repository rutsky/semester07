#ifndef LETTERPROXYMODEL_H
#define LETTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class LetterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath)

public:
    explicit LetterProxyModel(QObject *parent = 0);

public:
    QString rootPath() const;
    void setRootPath(QString const &path);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    QString rootPath_;
};

#endif // LETTERPROXYMODEL_H
