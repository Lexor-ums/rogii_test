#pragma once

#include <QFutureWatcher>
#include <QMap>
#include <QObject>

class QQmlApplicationEngine;
class QQmlComponent;
class QTcpSocket;
class QJsonObject;

/*!
 * \brief The UIController class бэк-энд для интерфейса
 */
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
    /*!
     * \brief sendMessageToServer отравка сообщения на сервер
     * \param sender имя отправителя
     * \param body текст сообщения
     */
    Q_INVOKABLE void sendMessageToServer(QString sender, QString body);
    /*!
     * \brief closeConnection закрытие соединения с польщователем
     * \param sender имя пользователя
     */
    Q_INVOKABLE void closeConnection(QString sender);
    /*!
     * \brief openNewChat открыть чат с пользхователем
     * \param sender имя пользователя
     */
    Q_INVOKABLE void openNewChat(QString sender);
signals:
private:
    /*!
     * \brief sendToServer отправка сообщеня на сервер
     * \param json данные о сообщении
     * \param sender имя пользоватея
     */
    void sendToServer(QJsonObject *json, const QString &sender);
    QQmlApplicationEngine *m_engine;
    QMap<QString, ChatWindow*> m_openedWindows;
    QFuture<void> writeFuture;
    QFutureWatcher<void> *writeWatcher;

private slots:
    /*!
     * \brief onReadyRead получение данных с сервера
     */
    void onReadyRead();
    /*!
     * \brief getHistory запрос истории сообщения пользователя
     * \param sender ия пользователя
     */
    void getHistory(QString sender);

};

