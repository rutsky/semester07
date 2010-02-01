#ifndef COMPOSERDIALOG_H
#define COMPOSERDIALOG_H

#include <QDialog>

namespace Ui {
    class ComposerDialog;
}

class ComposerDialog : public QDialog {
    Q_OBJECT
public:
    ComposerDialog(QWidget *parent = 0);
    ~ComposerDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ComposerDialog *ui;

private slots:
    void on_fileName_textChanged(QString );
    void on_saveButton_clicked();
};

#endif // COMPOSERDIALOG_H
