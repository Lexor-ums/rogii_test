#pragma once

#include <QFuture>
#include <QJsonDocument>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ClientImitator : public QObject
{
    Q_OBJECT
public:
    explicit ClientImitator(QObject *parent = nullptr);
    void setSocket(qintptr descriptor);

signals:
    void clientConected();

public slots:
    void initiateWrite(const QJsonDocument &msg);
private slots:

    void initiateRead();
    void readFinished();
    void writeFinished();
private:
    QJsonDocument startRead(const QByteArray &data);
    QJsonDocument startWrite(const QJsonDocument &data);
    int m_port;
    bool isWorking;
    QTcpSocket* m_socket;
    QString m_adress;
    QHash<long long, QTcpSocket* > m_serverSessions;
    QFuture<QJsonDocument> readFuture;
    QFutureWatcher<QJsonDocument> *readWatcher;
    QFuture<QJsonDocument> writeFuture;
    QFutureWatcher<QJsonDocument> *writeWatcher;

};

