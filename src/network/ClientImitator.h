#pragma once

#include <QFuture>
#include <QJsonDocument>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

/*!
 * \brief The ClientImitator class класс реализующий заботу с соединением
 */

class ClientImitator : public QObject
{
    Q_OBJECT
public:
    explicit ClientImitator(QObject *parent = nullptr);
    /*!
     * \brief setSocket создаёт сокет для раболты с клиентом
     * \param descriptor дескриптор сокета
     */
    void setSocket(qintptr descriptor);

signals:
    void clientConected();

public slots:
    /*!
     * \brief initiateWrite инициализации процесса ответа клиету
     * \param msg Json сообщение
     */
    void initiateWrite(const QJsonDocument &msg);
private slots:
    /*!
     * \brief initiateRead инициализаци процесса чтения данных
     */
    void initiateRead();
    /*!
     * \brief readFinished слот для пост обработки данных после чтения
     */
    void readFinished();
    /*!
     * \brief writeFinished слот для пост обработки данных для записи
     */
    void writeFinished();
private:
    /*!
     * \brief startRead начало орбрабьотка данных из сети
     * \param data массив байт
     * \return первый агремент 0 - ответ клиенту не нуженб иначе 1. Втрой аргумент Json сообщение
     * клиенту
     */
    QPair<bool, QJsonDocument> startRead(const QByteArray &data);
    /*!
     * \brief startWrit инициализаци процесса рьработки данных для записи
     * \param datadata массив байт
     * \return Json сообщение
     */
    QJsonDocument startWrite(const QJsonDocument &data);
    int m_port;
    bool isWorking;
    QTcpSocket* m_socket;
    QString m_adress;
    QHash<long long, QTcpSocket* > m_serverSessions;
    QFuture< QPair<bool, QJsonDocument>> readFuture;
    QFutureWatcher< QPair<bool, QJsonDocument>> *readWatcher;
    QFuture<QJsonDocument> writeFuture;
    QFutureWatcher<QJsonDocument> *writeWatcher;

};

