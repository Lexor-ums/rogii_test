#include "UserListItem.h"

UserListItem::UserListItem(QObject *parent) : QObject(parent)
{

}

UserListItem::UserListItem(const QString &name, QObject *parent) : QObject(parent),
    m_name(name)
{

}

QString UserListItem::getName() const
{
    return m_name;
}

void UserListItem::setName(const QString &name)
{
    m_name = name;
}
