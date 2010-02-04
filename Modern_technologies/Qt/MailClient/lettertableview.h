#ifndef LETTERTABLEVIEW_H
#define LETTERTABLEVIEW_H

#include <QTableView>

class LetterTableView : public QTableView
{
    Q_OBJECT
public:
    explicit LetterTableView(QWidget *parent = 0);

signals:

private slots:
    void on_customContextMenuRequested(const QPoint &);
    void on_contextMenu_toggled(int section);
};

#endif // LETTERTABLEVIEW_H
