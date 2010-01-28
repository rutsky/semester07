#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QObject>

#include "ui_about.h"

class AboutDialog : public QDialog, private Ui::AboutDialog
{
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = 0);
};

#endif // ABOUTDIALOG_H
