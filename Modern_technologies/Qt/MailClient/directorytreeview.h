#ifndef DIRECTORYTREEVIEW_H
#define DIRECTORYTREEVIEW_H

#include <QTreeView>

class DirectoryTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit DirectoryTreeView(QWidget *parent = 0);

signals:

public slots:
    //void updateRootDirectory(  );
};

#endif // DIRECTORYTREEVIEW_H
