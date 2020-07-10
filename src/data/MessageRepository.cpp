#include "MessageRepository.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

MessageRepository::MessageRepository(QObject *parent) : QObject(parent)
{

}

void MessageRepository::addMessage(const QString &name, const QByteArray &data)
{
    for (auto &messageList : m_messageMap){
        messageList.push_back(Message(data));
    }
    emit signalNewMesage(m_messageMap[name].last());
}

QJsonArray MessageRepository::getAllMessages(const QString &name)
{
    QJsonArray array;
    for (auto message : m_messageMap[name]){
        array.append(QJsonValue(message.toJSon()));
    }
    return array;
}
