#ifndef LETTERTABLEVIEW_H
#define LETTERTABLEVIEW_H

#include <QTableView>

class LetterTableView : public QTableView
{
    Q_OBJECT
public:
    explicit LetterTableView(QWidget *parent = 0);

signals:

public slots:
    void rootDirectoryChanged(QString const &);
};

#endif // LETTERTABLEVIEW_H
