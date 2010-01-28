#include <QFileSystemModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QString const maildir = QDir("../maildir").absolutePath();
    fileSystemModel->setRootPath(maildir);
    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setRootIndex(fileSystemModel->index(maildir));
    ui->treeView->setColumnHidden(1, true);
    ui->treeView->setColumnHidden(2, true);
    ui->treeView->setColumnHidden(3, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::on_treeView_customContextMenuRequested(QPoint pos)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("&New"), this, SLOT(newDirectory()))->setToolTip(tr("Create a new directory"));
    menu->addAction(tr("&Remove"), this, SLOT(newDirectory()))->setToolTip(tr("Remove directory"));
    menu->exec(ui->treeView->mapToGlobal(pos));
}

void MainWindow::newDirectory()
{

}

void MainWindow::removeDirectory()
{

}
