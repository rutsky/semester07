#include "directorytreeview.h"

DirectoryTreeView::DirectoryTreeView(QWidget *parent) :
    QTreeView(parent)
{
}

void DirectoryTreeView::currentChanged(const QModelIndex & current, const QModelIndex & previous)
{
    QTreeView::currentChanged(current, previous);


}
