#pragma once

#include <QObject>

class UserListItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY signalNameChanged)
public:
    explicit UserListItem(QObject *parent = nullptr);
    explicit UserListItem(const QString &name, QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);
signals:
    void signalNameChanged(QString &name);
private:
    QString m_name;
};

