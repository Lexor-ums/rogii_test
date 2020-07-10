#include "MessageRepository.h"

#include <QJsonArray>
#include <QJsonDocument>

MessageRepository::MessageRepository(QObject *parent) : QObject(parent)
{

}

void MessageRepository::addMessage(const QString &name, const QByteArray &data)
{
    m_messageMap[name].append(Message(data));
}

QJsonArray MessageRepository::getAllMessages(const QString &name)
{
    QJsonArray array;
    for (auto message : m_messageMap[name]){
        array.append(QJsonValue(message.toJSon()));
    }
    return array;
}
