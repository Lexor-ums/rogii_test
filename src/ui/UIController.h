#pragma once

#include <QFutureWatcher>
#include <QMap>
#include <QObject>

class QQmlApplicationEngine;
class QQmlComponent;
class QTcpSocket;
class QJsonObject;

class UIController : public QObject
{
    Q_OBJECT
    struct ChatWindow{
        QSharedPointer<QQmlComponent> component;
        QSharedPointer<QObject> object;
        QTcpSocket *socket;
    };

public:
    explicit UIController(QQmlApplicationEngine *engine, QObject *parent = nullptr);
     ~UIController();
    explicit UIController(QObject *parent = nullptr);
    Q_INVOKABLE void sendMessageToServer(QString sender, QString body);
    Q_INVOKABLE void closeConnection(QString sender);
    Q_INVOKABLE void openNewChat(QString sender);
signals:
private:
    void sendToServer(QJsonObject *json, const QString &sender);
    QQmlApplicationEngine *m_engine;
    QMap<QString, ChatWindow*> m_openedWindows;
    QFuture<void> writeFuture;
    QFutureWatcher<void> *writeWatcher;

private slots:
    void onReadyRead();
    void getHistory(QString sender);

};

