#ifndef DIRECTORYTREEVIEW_H
#define DIRECTORYTREEVIEW_H

#include <QTreeView>

class DirectoryTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit DirectoryTreeView(QWidget *parent = 0);

protected:
    void currentChanged(const QModelIndex & current, const QModelIndex & previous);

signals:

public slots:
    //void updateRootDirectory(  );
};

#endif // DIRECTORYTREEVIEW_H
