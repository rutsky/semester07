#include <QDir>

#include "composerdialog.h"
#include "ui_composerdialog.h"

#include "letterobject.h"

ComposerDialog::ComposerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComposerDialog)
{
    ui->setupUi(this);

    ui->saveButton->setEnabled(!ui->fileName->text().isEmpty());
    ui->loadButton->setEnabled(!ui->fileName->text().isEmpty());
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
    letter.setText(ui->textEdit->toHtml());
    letter.save(ui->fileName->text());
}

void ComposerDialog::on_fileName_textChanged(QString newText)
{
    ui->saveButton->setEnabled(!newText.isEmpty());
    ui->loadButton->setEnabled(!newText.isEmpty());
}

void ComposerDialog::on_loadButton_clicked()
{
    QScopedPointer<LetterObject> letter(LetterObject::load(ui->fileName->text()));
    ui->senderEdit->setText(letter->sender());
    ui->sentDateTimeEdit->setDateTime(letter->sentDate());
    ui->receiveDateTimeEdit->setDateTime(letter->receivedDate());
    ui->subjectEdit->setText(letter->subject());
    ui->textEdit->setHtml(letter->text());
}
