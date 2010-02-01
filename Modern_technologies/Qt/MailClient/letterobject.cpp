#include <QFile>
#include <QDataStream>

#include "letterobject.h"

LetterObject::LetterObject(QObject *parent) :
    QObject(parent)
{
}

LetterObject::~LetterObject()
{

}

LetterObject * LetterObject::load(QString const &filePath, QObject *parent)
{
    // TODO: Handle saving errors.
    LetterObject *letter = new LetterObject(parent);

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    stream >> letter->sender_ >> letter->sentDate_ >> letter->receivedDate_ >> letter->subject_ >> letter->text_;

    return letter;
}

void LetterObject::save(QString const &filePath) const
{
    // TODO: Handle loading errors.
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);    // read the data serialized from the file

    stream << sender() << sentDate() << receivedDate() << subject() << text();
}

QString LetterObject::sender() const
{
    return sender_;
}

QDateTime LetterObject::sentDate() const
{
    return sentDate_;
}

QDateTime LetterObject::receivedDate() const
{
    return receivedDate_;
}

QString LetterObject::subject() const
{
    return subject_;
}

int LetterObject::size() const
{
    return text_.length();
}

QString LetterObject::text() const
{
    return text_;
}

void LetterObject::setSender(QString const &newSender)
{
    sender_ = newSender;
}

void LetterObject::setSentDate(QDateTime const &newSentDate)
{
    sentDate_ = newSentDate;
}

void LetterObject::setReceivedDate(QDateTime const &newReceivedDate)
{
    receivedDate_ = newReceivedDate;
}

void LetterObject::setSubject(QString const &newSubject)
{
    subject_ = newSubject;
}

void LetterObject::setText(QString const &newText)
{
    text_ = newText;
}
