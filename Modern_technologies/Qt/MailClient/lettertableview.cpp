#include "lettertableview.h"

#include "letterheaderview.h"

LetterTableView::LetterTableView(QWidget *parent) :
    QTableView(parent)
{
    setHorizontalHeader(new LetterHeaderView()); // TODO: Check is memory is managed correctly
}
