#pragma once

#include <QObject>

/*!
 * \brief The UserListItem class класс, описывающий подльзователея
 */
class UserListItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY signalNameChanged)
public:
    explicit UserListItem(QObject *parent = nullptr);
    explicit UserListItem(const QString &name, QObject *parent = nullptr);

    /*!
     * \brief getName получения имени пользолвателя
     * \return имя пользователя
     */
    QString getName() const;
    /*!
     * \brief setName установка тмени пользоватиеля
     * \param name имя пользователя
     */
    void setName(const QString &name);
signals:
    void signalNameChanged(QString &name);
private:
    QString m_name;
};

