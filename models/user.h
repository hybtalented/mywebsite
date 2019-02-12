#ifndef USER_H
#define USER_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractUser>
#include <TAbstractModel>

class TModelObject;
class UserObject;
class QJsonArray;


class T_MODEL_EXPORT User : public TAbstractUser, public TAbstractModel
{
public:
    User();
    User(const User &other);
    User(const UserObject &object);
    ~User();

    int id() const;
    QString username() const;
    void setUsername(const QString &username);
    QString password() const;
    void setPassword(const QString &password);
    QString createdAt() const;
    QString updatedAt() const;
    QString email() const;
    void setEmail(const QString &email);
    QByteArray icon() const;
    void setIcon(const QByteArray &icon);
    QString identityKey() const { return username(); }
    User &operator=(const User &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static User authenticate(const QString &username, const QString &password);
    static User create(const QString &username, const QString &password, const QString &email, const QByteArray &icon);
    static User create(const QVariantMap &values);
    static User get(int id);
    static User get(const QString& name);
    static int count();
    static QList<User> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<UserObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
    friend QDataStream &operator<<(QDataStream &ds, const User &model);
    friend QDataStream &operator>>(QDataStream &ds, User &model);
};

Q_DECLARE_METATYPE(User)
Q_DECLARE_METATYPE(QList<User>)

#endif // USER_H
