#pragma once

#include <QObject>
#include "UserListItem.h"
#include <QQmlListProperty>

/*!
 * \brief The UserListModel class класс описывающе моледб списка пользователей
 */
class UserListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<UserListItem> data READ data NOTIFY dataChanged)
    Q_CLASSINFO("DefaultProperty", "data")
    QQmlListProperty<UserListItem> data();
public:
    explicit UserListModel(QObject *parent = nullptr);
    /*!
     * \brief add дорбавить пользователя
     * \param name имя пользователя
     */
    Q_INVOKABLE void add(const QString &name);
    /*!
     * \brief isNameExist проверка на достепность имени пользователя
     * \param name имя пользователя
     * \return 0 - имя достепно, 1 - имя недостепно
     */
    Q_INVOKABLE bool isNameExist(const QString &name);
    /*!
     * \brief remove уджаление пользователя
     * \param pos позиция в с писке
     * \return
     */
    Q_INVOKABLE bool remove(int pos);
    /*!
     * \brief at полечения информации о пользователе
     * \param pos позиция в списке
     * \return
     */
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
