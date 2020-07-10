#include <QTcpServer>

#pragma once


class Sesrver : public QTcpServer
{
public:
    Sesrver(QObject *parent = nullptr);
    void startServer(const QString &address, int port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

