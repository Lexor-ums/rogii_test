#include <QTcpServer>

#pragma once

/*!
 * \brief The Sesrver class инветающий за имитаци сервера чата
 */
class Sesrver : public QTcpServer
{
public:
    Sesrver(QObject *parent = nullptr);
    /*!
     * \brief startServer запуст сервера
     * \param address адрес сервера
     * \param port порт сервера
     */
    void startServer(const QString &address, int port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

