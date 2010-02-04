#ifndef LETTERTABLEVIEW_H
#define LETTERTABLEVIEW_H

#include <QTableView>

class LetterTableView : public QTableView
{
    Q_OBJECT
public:
    explicit LetterTableView(QWidget *parent = 0);

    //void setSortingEnabled(bool _enable);

signals:
    void showLetter(QString const &letterFilePath);

protected slots:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);

private slots:
    void on_customContextMenuRequested(const QPoint &);
    void on_contextMenu_toggled(int section);
};

#endif // LETTERTABLEVIEW_H
