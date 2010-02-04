#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QSignalMapper>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>

#include "lettertableview.h"

#include "letterheaderview.h"

LetterTableView::LetterTableView(QWidget *parent) :
    QTableView(parent)
{
    QHeaderView *horizontal = new LetterHeaderView(); // TODO: Check is memory is managed correctly
    horizontal->setClickable(true);
    horizontal->setMovable(true);
    horizontal->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(horizontal, SIGNAL(customContextMenuRequested(const QPoint &)),
            SLOT(on_customContextMenuRequested(const QPoint &)));

    setHorizontalHeader(horizontal);
}

void LetterTableView::on_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu;

    QSignalMapper *signalMapper = new QSignalMapper(this);

    bool const oneSectionShown = (horizontalHeader()->hiddenSectionCount() == horizontalHeader()->count() - 1);
    for (int section = 0; section < horizontalHeader()->count(); ++section)
    {
        QString const columnName = model()->headerData(section, Qt::Horizontal, Qt::DisplayRole).toString();

        QAction *action = new QAction(columnName, menu);
        action->setCheckable(true);
        bool const hidden = horizontalHeader()->isSectionHidden(section);
        action->setChecked(!hidden);
        if (oneSectionShown && !hidden)
            action->setEnabled(false);

        connect(action, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping(action, section);

        menu->addAction(action);
    }

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(on_contextMenu_toggled(int)));

    menu->exec(mapToGlobal(pos));
}

void LetterTableView::on_contextMenu_toggled(int section)
{
    horizontalHeader()->setSectionHidden(section, !horizontalHeader()->isSectionHidden(section));
}

void LetterTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QTableView::currentChanged(current, previous);

    QSortFilterProxyModel *proxyModel = static_cast<QSortFilterProxyModel *>(model());
    QFileSystemModel *fileSystemModel = static_cast<QFileSystemModel *>(proxyModel->sourceModel());
    emit showLetter(fileSystemModel->filePath(proxyModel->mapToSource(current)));
}

// From http://www.qtcentre.org/threads/4270-QSortFilterProxyModel-lessThan-method-doesn-t-work!
/*
void LetterTableView::setSortingEnabled(bool _enable)
{
     horizontalHeader()->setSortIndicatorShown(_enable);

     if (_enable)
     {
         disconnect(horizontalHeader(), SIGNAL(sectionPressed(int)),
                    this, SLOT(selectColumn(int)));

         connect(horizontalHeader(), SIGNAL(sectionClicked(int)),
                    this, SLOT(sortByColumn(int)));

         sortByColumn(horizontalHeader()->sortIndicatorSection());
     }
     else
     {
         connect(horizontalHeader(), SIGNAL(sectionPressed(int)),
                    this, SLOT(selectColumn(int)));

         disconnect(horizontalHeader(), SIGNAL(sectionClicked(int)),
                    this, SLOT(sortByColumn(int)));
     }
}
*/
