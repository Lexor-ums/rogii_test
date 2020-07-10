#pragma once

#include <QMap>
#include <QObject>
#include "Message.h"

class Message;

/*!
 * \brief The MessageRepository class класс обеспечивающи хранение сообщений
 */
class MessageRepository : public QObject
{
    Q_OBJECT
public:
    explicit MessageRepository(QObject *parent = nullptr);
    /*!
     * \brief addMessage добавление сообщения в хранилище
     * \param name имя отправителя
     * \param data сообщение
     */
    void addMessage(const QString &name,  const QByteArray &data);
    /*!
     * \brief getAllMessages получить все сообщения для пользователя
     * \param name имя пользователя
     * \return массив соообщения в формате  JSon
     */
    QJsonArray getAllMessages(const QString &name);
signals:
    void signalNewMesage(const Message &mess);
private:
    QMap<QString, QList<Message>> m_messageMap;

};

