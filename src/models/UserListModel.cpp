#include "UserListModel.h"

UserListModel::UserListModel(QObject *parent) : QObject(parent)
{
    dataList.push_back(new  UserListItem("name"));

}

QQmlListProperty<UserListItem> UserListModel::data()
{
    return QQmlListProperty<UserListItem>(static_cast<QObject *>(this), static_cast<void *>(&dataList),
                                     &UserListModel::appendData, &UserListModel::countData,
                                     &UserListModel::atData, &UserListModel::clearData);
}

void UserListModel::add(const QString &name)
{
    dataList.push_back(new  UserListItem(name));
    emit dataChanged();
}

bool UserListModel::isNameExist(const QString &name)
{
    for (auto data : dataList){
        if (data->getName() == name)
            return true;
    }
    return false;
}

bool UserListModel::remove(int pos)
{
    dataList.removeAt(pos);
    emit dataChanged();
}

UserListItem *UserListModel::at(int pos)
{
    return dataList.at(pos);
}

void UserListModel::appendData(QQmlListProperty<UserListItem> *list, UserListItem *value)
{
    QList<UserListItem*> *data = static_cast<QList<UserListItem*> *>(list->data);
    data->append(value);
}

int UserListModel::countData(QQmlListProperty<UserListItem> *list)
{
    QList<UserListItem*> *data = static_cast<QList<UserListItem*> *>(list->data);
    return data->size();
}

UserListItem *UserListModel::atData(QQmlListProperty<UserListItem> *list, int index)
{
    QList<UserListItem*> *data = static_cast<QList<UserListItem*> *>(list->data);
    return data->at(index);
}

void UserListModel::clearData(QQmlListProperty<UserListItem> *list)
{
    QList<UserListItem*> *data = static_cast<QList<UserListItem*> *>(list->data);
    qDeleteAll(data->begin(), data->end());
    data->clear();
}
