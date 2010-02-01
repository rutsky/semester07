#ifndef LETTEROBJECT_H
#define LETTEROBJECT_H

#include <QObject>
#include <QString>
#include <QDateTime>

class LetterObject : public QObject
{
    Q_OBJECT
public:
    LetterObject(QObject *parent = 0);
    ~LetterObject();

    static LetterObject * load(QString const &filePath, QObject *parent = 0);
    void                  save(QString const &filePath) const;

    QString   sender() const;
    QDateTime sentDate() const;
    QDateTime receivedDate() const;
    QString   subject() const;
    int       size() const;
    QString   text() const;

    void setSender(QString const &sender);
    void setSentDate(QDateTime const &sentDate);
    void setReceivedDate(QDateTime const &receiveDate);
    void setSubject(QString const &subject);
    void setText(QString const &text);

private:
    QString   sender_;
    QDateTime sentDate_;
    QDateTime receivedDate_;
    QString   subject_;
    QString   text_;
};

#endif // LETTEROBJECT_H
