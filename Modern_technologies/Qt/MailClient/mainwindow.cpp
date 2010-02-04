#include <QFileSystemModel>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "directoryproxymodel.h"
#include "letterproxymodel.h"
#include "letterobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileSystemModel = new QFileSystemModel; // TODO: Check is memory is managed correctly
    fileSystemModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QString const maildir = QDir("../maildir").absolutePath();
    QModelIndex rootIndex = fileSystemModel->setRootPath(maildir);
    fileSystemModel->setReadOnly(false);

    directoryProxyModel = new DirectoryProxyModel; // TODO: Check is memory is managed correctly
    directoryProxyModel->setDynamicSortFilter(true);
    directoryProxyModel->setSourceModel(fileSystemModel);

    ui->treeView->setModel(directoryProxyModel);
    ui->treeView->setRootIndex(directoryProxyModel->mapFromSource(rootIndex));
    // TODO: Some items can have other number of columns!
    for (int i = 1; i < fileSystemModel->columnCount(QModelIndex()); ++i)
        ui->treeView->setColumnHidden(i, true);

    letterProxyModel = new LetterProxyModel; // TODO: Check is memory is managed correctly
    letterProxyModel->setDynamicSortFilter(true);
    letterProxyModel->setSourceModel(fileSystemModel);
    letterProxyModel->setFilterRegExp(QRegExp("\\.letter$", Qt::CaseInsensitive, QRegExp::RegExp));
    letterProxyModel->setFilterKeyColumn(0); // TODO
    letterProxyModel->setRootPath(maildir);

    ui->tableView->setModel(letterProxyModel);
    ui->tableView->horizontalHeader()->reset();
    ui->tableView->setRootIndex(letterProxyModel->mapFromSource(rootIndex));

    connect(ui->treeView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(directoryChanged(QModelIndex, QModelIndex)));

    connect(ui->tableView, SIGNAL(showLetter(QString const &)), this, SLOT(on_showLetter(QString const &)));
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

void MainWindow::directoryChanged(QModelIndex const &current, QModelIndex const &/* previous */)
{
    QModelIndex const sourceIndex = directoryProxyModel->mapToSource(current);
    letterProxyModel->setRootPath(fileSystemModel->filePath(sourceIndex));
    ui->tableView->setRootIndex(letterProxyModel->mapFromSource(sourceIndex));
}

void MainWindow::on_showLetter(QString const &letterFilePath)
{
    QScopedPointer<LetterObject> letter(LetterObject::load(letterFilePath));
    ui->textBrowser->setHtml(letter->text());
}
