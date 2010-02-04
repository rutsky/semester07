#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QSignalMapper>

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


    for (int section = 0; section < horizontalHeader()->count(); ++section)
    {
        QString const columnName = model()->headerData(section, Qt::Horizontal, Qt::DisplayRole).toString();

        QAction *action = new QAction(columnName, menu);
        action->setCheckable(true);
        action->setChecked(horizontalHeader()->isSectionHidden(section));

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
