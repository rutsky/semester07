#ifndef LETTERPROXYMODEL_H
#define LETTERPROXYMODEL_H

#include <QSortFilterProxyModel>

#include <QStringList>

class QFileSystemModel;

class LetterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath)

public:
    explicit LetterProxyModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

public:
    QString rootPath() const;
    void setRootPath(QString const &path);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

protected:
    QFileSystemModel const *sourceFileSystemModel() const;

private:
    QStringList columns_;
    QString rootPath_;
};

#endif // LETTERPROXYMODEL_H
