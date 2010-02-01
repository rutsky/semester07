#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QFileSystemModel;
class QAction;
class QModelIndex;
class QSortFilterProxyModel;

class DirectoryProxyModel;
class LetterProxyModel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_treeView_customContextMenuRequested(QPoint pos);
    void on_actionAbout_triggered();
    void newDirectory();
    void removeDirectory();
    void directoryChanged(QModelIndex const &current, QModelIndex const &previous);

private:
    QFileSystemModel    *fileSystemModel;
    DirectoryProxyModel *directoryProxyModel;
    LetterProxyModel    *letterProxyModel;
};

#endif // MAINWINDOW_H
