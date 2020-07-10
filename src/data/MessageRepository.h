#pragma once

#include <QMap>
#include <QObject>
#include "Message.h"

class Message;

class MessageRepository : public QObject
{
    Q_OBJECT
public:
    explicit MessageRepository(QObject *parent = nullptr);
    void addMessage(const QString &name,  const QByteArray &data);
    QJsonArray getAllMessages(const QString &name);
signals:
private:
    QMap<QString, QList<Message>> m_messageMap;

};

