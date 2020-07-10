#pragma once

#include <QJsonObject>
#include <QString>

class Message
{
public:
    Message();
    Message( const QByteArray &data);
    QJsonObject toJSon();
    static Message fromJson(const QJsonObject &messageBody);
    static QList<Message> fromJsonArray(const QJsonArray &messageBody);

    QString time() const;

    QString sender() const;

    QString body() const;

private:
    QString m_time;
    QString m_sender;
    QString m_body;
};

