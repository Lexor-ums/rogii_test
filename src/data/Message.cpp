#include "Message.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include <QDebug>
Message::Message()
{

}

Message::Message(const QByteArray &data)
{    QJsonDocument doc = QJsonDocument::fromJson(data);
     QJsonObject object  = doc.object();
    if (object.contains("time") && object["time"].isString())
        m_time = object["time"].toString();
    if (data.contains("sender") && object["sender"].isString())
        m_sender = object["sender"].toString();
    if (data.contains("body") && object["body"].isString())
        m_body = object["body"].toString();
}

QJsonObject Message::toJSon() const
{
    return QJsonObject
    {
        {"command","send_message"},
        {"time", m_time},
        {"sender", m_sender},
        {"body", m_body}
    };
}

Message Message::fromJson(const QJsonObject &messageBody)
{
    Message message;
    if (messageBody.contains("time") && messageBody["time"].isString())
        message.m_time = messageBody["time"].toString();
    if (messageBody.contains("sender") && messageBody["sender"].isString())
        message.m_sender = messageBody["sender"].toString();
    if (messageBody.contains("body") && messageBody["body"].isString())
        message.m_body = messageBody["body"].toString();
    return message;
}

QList<Message> Message::fromJsonArray(const QJsonArray &messageBody)
{
    QList<Message> messageList;

    for (auto it = messageBody.constBegin(); it != messageBody.constEnd(); ++it)
    {
        Message message;
        QJsonObject messageObject =  (*it).toObject();
        if (messageObject.contains("time") && messageObject["time"].isString())
            message.m_time = messageObject["time"].toString();
        if (messageObject.contains("sender") && messageObject["sender"].isString())
            message.m_sender = messageObject["sender"].toString();
        if (messageObject.contains("body") && messageObject["body"].isString())
            message.m_body = messageObject["body"].toString();
        messageList.push_back(message);
    }
    return messageList;
}

QString Message::time() const
{
    return m_time;
}

QString Message::sender() const
{
    return m_sender;
}

QString Message::body() const
{
    return m_body;
}
