#pragma once

#include <QObject>
#include "UserListItem.h"
#include <QQmlListProperty>

class UserListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<UserListItem> data READ data NOTIFY dataChanged)
    Q_CLASSINFO("DefaultProperty", "data")
    QQmlListProperty<UserListItem> data();
public:
    explicit UserListModel(QObject *parent = nullptr);
    Q_INVOKABLE void add(const QString &name);
    Q_INVOKABLE bool isNameExist(const QString &name);
    Q_INVOKABLE bool remove(int pos);
    Q_INVOKABLE UserListItem* at(int pos);
private:
    static void appendData(QQmlListProperty<UserListItem> *list, UserListItem *value);
    static int countData(QQmlListProperty<UserListItem> *list);
    static UserListItem *atData(QQmlListProperty<UserListItem> *list, int index);
    static void clearData(QQmlListProperty<UserListItem> *list);
    QList<UserListItem*> dataList;
signals:
    void dataChanged();
};
