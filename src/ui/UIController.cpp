#include "UIController.h"

#include <Message.h>
#include <QHostAddress>
#include <QJsonObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QTcpSocket>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

UIController::UIController(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent),
    m_engine(engine)
{
    writeWatcher = new QFutureWatcher<void>();
}

UIController::~UIController()
{
    for (auto window : m_openedWindows)
    {
        window->socket->disconnectFromHost();
    }
}

UIController::UIController(QObject *parent) : QObject(parent)
{

}

void UIController::sendMessageToServer(QString sender, QString body)
{
    QJsonObject *message = new QJsonObject( {
                                            {"command", "send_message"},
                                            {"sender", sender},
                                            {"time", QTime::currentTime().toString()},
                                            {"body", body},
                                        });
    writeFuture = QtConcurrent::run(this, &UIController::sendToServer, message, sender);
    writeWatcher->setFuture(writeFuture);
}

void UIController::closeConnection(QString sender)
{
    if (!m_openedWindows.contains(sender))
        return;
    disconnect(m_openedWindows[sender]->socket, &QTcpSocket::readyRead,
               this, &UIController::onReadyRead);
    m_openedWindows[sender]->socket->disconnectFromHost();
    m_openedWindows.remove(sender);
}

void UIController::openNewChat(QString sender)
{

    QTcpSocket *socket = m_openedWindows.contains(sender) ? m_openedWindows[sender]->socket
                                                          : new QTcpSocket;
    connect(socket, &QTcpSocket::connected, [this, sender, socket](){
                ChatWindow *chatWindow = new ChatWindow;
                QQmlComponent *component = new QQmlComponent(m_engine, QUrl(QStringLiteral("qrc:/ChatWindow.qml")));

                QObject *object = component->create();
                object->setProperty("userName", sender);
                chatWindow->component = QSharedPointer<QQmlComponent>(component);
                chatWindow->object = QSharedPointer<QObject>(object);
                chatWindow->socket = socket;
                m_openedWindows[sender] = chatWindow;
                QTimer::singleShot(100, [this, sender](){
                    getHistory(sender);
                });
    });
    connect(socket, &QTcpSocket::readyRead, this, &UIController::onReadyRead, Qt::DirectConnection);
    socket->connectToHost(QHostAddress("127.0.0.1"), 3000);
}

void UIController::getHistory(QString sender)
{
    QJsonObject *message = new QJsonObject( {
                                            {"command", "get_history"},
                                            {"sender", sender}
                                        });
    writeFuture = QtConcurrent::run(this, &UIController::sendToServer, message, sender);
    writeWatcher->setFuture(writeFuture);
}

void UIController::sendToServer(QJsonObject *json, const QString &sender)
{
    auto window = m_openedWindows[sender];
    QJsonDocument doc(*json);
    QByteArray bytes = doc.toJson();
    qDebug()<<"send to server"<<window->socket->write(bytes, bytes.size());
    window->socket->flush();
}

void UIController::onReadyRead()
{
    QTcpSocket* sock = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = sock->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject object  = doc.object();
    if (object.contains("command") && object["command"].isString())
    {
        QString command = object["command"].toString();
        if (command == "send_message")
        {
            Message message = Message::fromJson(object);
            auto chatWindow = std::find_if(m_openedWindows.constBegin(), m_openedWindows.constEnd(),
                                           [sock](ChatWindow *it){
                if(it->socket == sock)
                    return true;
                return false;
            });
            if (chatWindow == m_openedWindows.constEnd())
                return;
            QMetaObject::invokeMethod(chatWindow.value()->object.data(), "getNewMessage",
                    Q_ARG(QVariant, message.time()), Q_ARG(QVariant, message.sender()),
                    Q_ARG(QVariant, message.body()));
        }
        if (command == "history")
        {
            if (object.contains("data") && object["data"].isArray())
            {
                QList<Message> messageList = Message::fromJsonArray(object["data"].toArray());
                auto chatWindow = std::find_if(m_openedWindows.constBegin(), m_openedWindows.constEnd(),
                                               [sock](ChatWindow *it){
                    if(it->socket == sock)
                        return true;
                    return false;
                });
                if (chatWindow == m_openedWindows.constEnd())
                    return;
                for (auto mess : messageList){
                    QMetaObject::invokeMethod(chatWindow.value()->object.data(), "getNewMessage",
                            Q_ARG(QVariant, mess.time()), Q_ARG(QVariant, mess.sender()),
                            Q_ARG(QVariant, mess.body()));
                }
            }
        }
    }
}

