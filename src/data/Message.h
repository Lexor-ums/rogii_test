#pragma once

#include <QJsonObject>
#include <QString>

/*!
 * \brief The Message class класс хранащий сообщение от клиента
 */
class Message
{
public:
    Message();
    Message( const QByteArray &data);
    /*!
     * \brief toJSon преобразовывает стректурк в JSon формат
     * \return
     */
    QJsonObject toJSon() const;
    /*!
     * \brief fromJson преобразовывает JSon формат в стректуру сообщения
     * \param messageBody JSon форматированное сообщений
     * \return клас сообщения
     */
    static Message fromJson(const QJsonObject &messageBody);
    /*!
     * \brief fromJsonArray преобразовывает Json массив в массив сообщений
     * \param messageBody jSon массив
     * \return массив сообщений
     */
    static QList<Message> fromJsonArray(const QJsonArray &messageBody);

    /*!
     * \brief time полечение времени отправления
     * \return время отправления
     */
    QString time() const;
    /*!
     * \brief sender порлучения имени отправителя
     * \return имя отправителя
     */
    QString sender() const;

    /*!
     * \brief body получение текста сообщения
     * \return текс сообщения
     */
    QString body() const;

private:
    QString m_time;
    QString m_sender;
    QString m_body;
};

