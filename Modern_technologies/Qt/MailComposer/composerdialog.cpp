#include <QDir>

#include "composerdialog.h"
#include "ui_composerdialog.h"

#include "letterobject.h"

ComposerDialog::ComposerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComposerDialog)
{
    ui->setupUi(this);
}

ComposerDialog::~ComposerDialog()
{
    delete ui;
}

void ComposerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ComposerDialog::on_saveButton_clicked()
{
    LetterObject letter;
    letter.setSender(ui->senderEdit->text());
    letter.setSentDate(ui->sentDateTimeEdit->dateTime());
    letter.setReceivedDate(ui->receiveDateTimeEdit->dateTime());
    letter.setSubject(ui->subjectEdit->text());
    letter.setSubject(ui->textEdit->toHtml());
    letter.save(ui->fileName->text());
}

void ComposerDialog::on_fileName_textChanged(QString newText)
{
    ui->saveButton->setEnabled(!newText.isEmpty());
}
