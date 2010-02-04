#include <QFileSystemModel>
#include <QDebug>
#include <QInputDialog>

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

    //connect(ui->tableView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
    //        this, SLOT(updateLetter()));
    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(updateLetter()));
    //connect(ui->treeView->selectionModel(),  SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
    //        this, SLOT(updateLetter()));
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
    QAction *action;

    action = new QAction(tr("&New"), this);
    action->setToolTip(tr("Create a new directory"));
    connect(action, SIGNAL(triggered()), this, SLOT(newDirectory()));
    menu->addAction(action);

    action = new QAction(tr("&Remove"), this);
    action->setToolTip(tr("Remove directory"));
    if (ui->treeView->selectionModel()->selection().isEmpty())
        action->setEnabled(false);
    connect(action, SIGNAL(triggered()), this, SLOT(removeDirectory()));
    menu->addAction(action);

    menu->exec(ui->treeView->mapToGlobal(pos));
}

void MainWindow::newDirectory()
{
    QModelIndex parentTreeIndex;
    if (ui->treeView->selectionModel()->selection().indexes().isEmpty())
        parentTreeIndex = ui->treeView->rootIndex();
    else
        parentTreeIndex = ui->treeView->selectionModel()->selection().indexes()[0];
    QModelIndex const fileSystemIndex = directoryProxyModel->mapToSource(parentTreeIndex);

    bool ok;
    QString const directoryName = QInputDialog::getText(this, tr("New directory"),
                                         tr("New directory name:"), QLineEdit::Normal,
                                            "New Folder", &ok);
    if (ok && !directoryName.isEmpty())
        fileSystemModel->mkdir(fileSystemIndex, directoryName);
}

void MainWindow::removeDirectory()
{
    QModelIndex const index = ui->treeView->selectionModel()->selection().indexes()[0];
    qDebug() << fileSystemModel->remove(directoryProxyModel->mapToSource(index));
}

void MainWindow::directoryChanged(QModelIndex const &current, QModelIndex const &/* previous */)
{
    QModelIndex const sourceIndex = directoryProxyModel->mapToSource(current);
    letterProxyModel->setRootPath(fileSystemModel->filePath(sourceIndex));
    ui->tableView->setRootIndex(letterProxyModel->mapFromSource(sourceIndex));

    //if (ui->tableView->model()->hasChildren(ui->tableView->rootIndex()))
    {
        //QModelIndex const firstChild = ui->tableView->model()->index(0, 0, ui->tableView->rootIndex());
        QModelIndex const topLeft = ui->tableView->model()->index(0, 0, ui->tableView->rootIndex());
        QModelIndex const bottomRight = ui->tableView->model()->index(0, 10, ui->tableView->rootIndex());
        ui->tableView->selectionModel()->select(QItemSelection(topLeft, bottomRight), QItemSelectionModel::ClearAndSelect);
        //ui->tableView->selectionModel()->setCurrentIndex(firstChild, QItemSelectionModel::Clear);
        //for (int i = 0; i < 10 /* TODO! */; ++i)
        //    ;//ui->tableView->selectionModel()->select(ui->tableView->model()->index(0, i, ui->tableView->rootIndex()), QItemSelectionModel::Select);
    }
    //else
    //    ;//ui->tableView->selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Clear);
}

void MainWindow::updateLetter()
{
    QModelIndexList const selection = ui->tableView->selectionModel()->selection().indexes();
    if (selection.empty() || !selection[0].isValid())
        //ui->textBrowser->setHtml("<h1>Select letter from list</h1>");
        ui->textBrowser->setHtml("");
    else
    {
        QModelIndex const index = selection[0];
        QString const letterFilePath = fileSystemModel->filePath(letterProxyModel->mapToSource(index));
        QScopedPointer<LetterObject> letter(LetterObject::load(letterFilePath));
        ui->textBrowser->setHtml(letter->text());
    }
}
