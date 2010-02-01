#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QFileSystemModel;
class QAction;

class DirectoryProxyModel;
class LetterProxyModel;
class QSortFilterProxyModel;

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

private:
    QFileSystemModel    *fileSystemModel;
    DirectoryProxyModel *directoryProxyModel;
    //LetterProxyModel    *letterProxyModel;
    QSortFilterProxyModel *letterProxyModel;
};

#endif // MAINWINDOW_H
