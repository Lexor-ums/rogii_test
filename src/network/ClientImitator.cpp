#include "ClientImitator.h"
#include <QtConcurrent/QtConcurrent>
#include "MessageRepository.h"

Q_GLOBAL_STATIC(MessageRepository, messageRepository)

ClientImitator::ClientImitator(QObject *parent) : QObject(parent)
{
    writeWatcher = new QFutureWatcher<QJsonDocument>();
    connect(writeWatcher, &QFutureWatcher<QJsonDocument>::finished, this, &ClientImitator::writeFinished);
    readWatcher = new QFutureWatcher<QJsonDocument>();
    connect(readWatcher, &QFutureWatcher<QJsonDocument>::finished, this, &ClientImitator::readFinished);
    isWorking = true;
}

void ClientImitator::setSocket(qintptr descriptor)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QAbstractSocket::disconnected, m_socket, &QAbstractSocket::deleteLater);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientImitator::initiateRead);
    m_socket->setSocketDescriptor(descriptor);

}

void ClientImitator::initiateWrite(const QJsonDocument &msg){
    if(!isWorking){
        return;
    }
    writeFuture = QtConcurrent::run(this, &ClientImitator::startWrite, msg);
    writeWatcher->setFuture(writeFuture);
}

void ClientImitator::initiateRead(){
    if(!isWorking){
        return;
    }
    QByteArray data = m_socket->readAll();
    readFuture = QtConcurrent::run(this, &ClientImitator::startRead, data);
    readWatcher->setFuture(readFuture);
}


void ClientImitator::readFinished(){
    QJsonDocument doc = readFuture.result();
    initiateWrite(doc);
}

void ClientImitator::writeFinished(){
    QJsonDocument doc = readFuture.result();
    QByteArray data = doc.toJson();

    qDebug()<<"send from serv "<<m_socket->write(data, data.size())<<m_socket->error()<<data.size();
    m_socket->flush();

}

 QJsonDocument ClientImitator::startRead(const QByteArray &data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonDocument docRes = QJsonDocument::fromJson(data);
    QJsonObject object  = doc.object();
    if (object.contains("command") && object["command"].isString())
    {
        QString command = object["command"].toString();
        if (command == "send_message")
        {
            if (object.contains("sender") && object["sender"].isString())
            {
                QString sender = object["sender"].toString();
                messageRepository->addMessage(sender, data);
                docRes = doc;
            }
        }
        if (command == "get_history")
        {
            if (object.contains("sender") && object["sender"].isString())
            {
                QJsonObject obj({
                                    {"command", "history"}
                                });
                QString sender = object["sender"].toString();
                QJsonArray array = messageRepository->getAllMessages(sender);
                obj.insert("data", QJsonValue(array));
                docRes.setObject(obj);
            }
        }
    }
    return docRes;
}

QJsonDocument ClientImitator::startWrite(const QJsonDocument &data){
    return data;
}

