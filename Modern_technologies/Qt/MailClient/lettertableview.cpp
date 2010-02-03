#include "lettertableview.h"

#include "letterheaderview.h"

LetterTableView::LetterTableView(QWidget *parent) :
    QTableView(parent)
{
    QHeaderView *horizontal = new LetterHeaderView(); // TODO: Check is memory is managed correctly
    horizontal->setClickable(true);
    setHorizontalHeader(horizontal);
}
