#include "ClientImitator.h"
#include "Sesrver.h"

Sesrver::Sesrver(QObject *parent) : QTcpServer(parent)
{

}

void Sesrver::startServer(const QString &address, int port)
{
    if(listen(QHostAddress(address), port))
    {
        qDebug() << "Server: started";
    }
    else
    {
        qCritical("Server: not started!");
    }
}

void Sesrver::incomingConnection(qintptr socketDescriptor)
{
    ClientImitator *client = new ClientImitator(this);
    client->setSocket(socketDescriptor);
}
