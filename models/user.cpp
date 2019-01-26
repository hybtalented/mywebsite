#include <TreeFrogModel>
#include "user.h"
#include "userobject.h"

User::User()
    : TAbstractUser(), TAbstractModel(), d(new UserObject())
{
    d->id = 0;
}

User::User(const User &other)
    : TAbstractUser(), TAbstractModel(), d(new UserObject(*other.d))
{ }

User::User(const UserObject &object)
    : TAbstractUser(), TAbstractModel(), d(new UserObject(object))
{ }


User::~User()
{
    // If the reference count becomes 0,
    // the shared data object 'UserObject' is deleted.
}
int User::id() const
{
	return d->id;
}
QString User::username() const
{
    return d->username;
}

void User::setUsername(const QString &username)
{
    d->username = username;
}

QString User::password() const
{
    return d->password;
}

void User::setPassword(const QString &password)
{
    d->password = password;
}

QString User::email() const{
    return d->email;
}

void User::setEmail(const QString& email){
    d->email=email;
}

QString User::createdAt() const
{
    return d->created_at;
}

QString User::updatedAt() const
{
    return d->updated_at;
}

User &User::operator=(const User &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

User User::authenticate(const QString &username, const QString &password)
{
    if (username.isEmpty() || password.isEmpty())
        return User();

    TSqlORMapper<UserObject> mapper;
    UserObject obj = mapper.findFirstBy(UserObject::Username,username);
    if (obj.isNull() || obj.password != password) {
        obj.clear();
    }
    return User(obj);
}

User User::create(const QString &username, const QString &password,const QString&email)
{
    UserObject obj;
    obj.username = username;
    obj.password = password;
    obj.email = email;
    if (!obj.create()) {
        return User();
    }
    return User(obj);
}

User User::create(const QVariantMap &values)
{
    User model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

User User::get(const QString& username)
{
    TSqlORMapper<UserObject> mapper;
    return User(mapper.findFirstBy(UserObject::Username,username));
}

int User::count()
{
    TSqlORMapper<UserObject> mapper;
    return mapper.findCount();
}

QList<User> User::getAll()
{
    return tfGetModelListByCriteria<User, UserObject>();
}

QJsonArray User::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<UserObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<UserObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(User(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *User::modelData()
{
    return d.data();
}

const TModelObject *User::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const User &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, User &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(User)