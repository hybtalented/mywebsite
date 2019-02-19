#include <TreeFrogModel>
#include "usergroup.h"
#include "usergroupobject.h"

Usergroup::Usergroup()
    : TAbstractModel(), d(new UsergroupObject())
{
    d->id = 0;
}

Usergroup::Usergroup(const Usergroup &other)
    : TAbstractModel(), d(new UsergroupObject(*other.d))
{ }

Usergroup::Usergroup(const UsergroupObject &object)
    : TAbstractModel(), d(new UsergroupObject(object))
{ }

Usergroup::~Usergroup()
{
    // If the reference count becomes 0,
    // the shared data object 'UsergroupObject' is deleted.
}

int Usergroup::id() const
{
    return d->id;
}

QString Usergroup::groupid() const
{
    return d->groupid;
}

void Usergroup::setGroupid(const QString &groupid)
{
    d->groupid = groupid;
}

QString Usergroup::userid() const
{
    return d->userid;
}

void Usergroup::setUserid(const QString &userid)
{
    d->userid = userid;
}

QString Usergroup::createdAt() const
{
    return d->created_at;
}

QString Usergroup::updatedAt() const
{
    return d->updated_at;
}

Usergroup &Usergroup::operator=(const Usergroup &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Usergroup Usergroup::create(const QString &groupid, const QString &userid)
{
    UsergroupObject obj;
    obj.groupid = groupid;
    obj.userid = userid;
    if (!obj.create()) {
        return Usergroup();
    }
    return Usergroup(obj);
}

Usergroup Usergroup::create(const QVariantMap &values)
{
    Usergroup model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Usergroup Usergroup::get(int id)
{
    TSqlORMapper<UsergroupObject> mapper;
    return Usergroup(mapper.findByPrimaryKey(id));
}

int Usergroup::count()
{
    TSqlORMapper<UsergroupObject> mapper;
    return mapper.findCount();
}

QList<Usergroup> Usergroup::getAll()
{
    return tfGetModelListByCriteria<Usergroup, UsergroupObject>(TCriteria());
}

QJsonArray Usergroup::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<UsergroupObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<UsergroupObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Usergroup(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Usergroup::modelData()
{
    return d.data();
}

const TModelObject *Usergroup::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Usergroup &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Usergroup &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Usergroup)
