#ifndef LETTERPROXYMODEL_H
#define LETTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class QFileSystemModel;

class LetterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath)

public:
    explicit LetterProxyModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

public:
    QString rootPath() const;
    void setRootPath(QString const &path);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

protected:
    QFileSystemModel const *sourceFileSystemModel() const;

private:
    QString rootPath_;
};

#endif // LETTERPROXYMODEL_H