#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QThread>
#include <Sesrver.h>
#include "UserListModel.h"
#include "UIController.h"
#include "ClientImitator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append(QDir::currentPath() + "/platforms");
    QCoreApplication::setLibraryPaths(paths);

    QGuiApplication app(argc, argv);
    UserListModel userListModel;
    QQmlApplicationEngine engine;
    QThread thread;
    Sesrver server;    
    qDebug()<<QCoreApplication::libraryPaths();
    server.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, [&server](){
        server.startServer("127.0.0.1", 3000);
    });
    thread.start();
    UIController controller(&engine);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<UserListModel>("UserListModel", 1, 0, "UserListModel");
    qmlRegisterType<UserListItem>("UserListItem", 1, 0, "UserListItem");
    qmlRegisterType<UIController>("UIController", 1, 0, "UIController");
    auto rootContgext = engine.rootContext();
    rootContgext->setContextProperty("userModel", &userListModel);
    rootContgext->setContextProperty("controller", &controller);
    engine.addImportPath(":/imports");
    engine.load(url);

    return app.exec();
}
