#include "ClientImitator.h"
#include <QtConcurrent/QtConcurrent>
#include "MessageRepository.h"

Q_GLOBAL_STATIC(MessageRepository, messageRepository)

ClientImitator::ClientImitator(QObject *parent) : QObject(parent)
{
    writeWatcher = new QFutureWatcher<QJsonDocument>();
    connect(writeWatcher, &QFutureWatcher<QJsonDocument>::finished, this, &ClientImitator::writeFinished);
    readWatcher = new QFutureWatcher<QPair<bool, QJsonDocument>>();
    connect(readWatcher, &QFutureWatcher<QJsonDocument>::finished, this, &ClientImitator::readFinished);
    isWorking = true;
    qRegisterMetaType<Message>("Message");
}

void ClientImitator::setSocket(qintptr descriptor)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientImitator::initiateRead);
    connect(messageRepository, &MessageRepository::signalNewMesage, this, [this](const Message &mess){
        initiateWrite(QJsonDocument(mess.toJSon()));
    }, Qt::QueuedConnection);
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
     QPair<bool, QJsonDocument> res = readFuture.result();
    if (res.first)
        initiateWrite(res.second);
}

void ClientImitator::writeFinished(){
    QJsonDocument doc = writeFuture.result();
    QByteArray data = doc.toJson();

    qDebug()<<" "<<m_socket->write(data, data.size())<<data<<m_socket;
    m_socket->flush();

}

 QPair<bool, QJsonDocument> ClientImitator::startRead(const QByteArray &data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QPair<bool, QJsonDocument> docRes = {false, QJsonDocument::fromJson(data) };
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
                docRes.second = doc;
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
                docRes.second = QJsonDocument(obj);
                docRes.first = true;
            }
        }
    }
    return docRes;
}

QJsonDocument ClientImitator::startWrite(const QJsonDocument &data){
    return data;
}

