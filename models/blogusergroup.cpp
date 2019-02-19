#include <TreeFrogModel>
#include "blogusergroup.h"
#include "blogusergroupobject.h"

Blogusergroup::Blogusergroup()
    : TAbstractModel(), d(new BlogusergroupObject())
{
    d->id = 0;
    d->usergroupid = 0;
    d->bloggroupid = 0;
}

Blogusergroup::Blogusergroup(const Blogusergroup &other)
    : TAbstractModel(), d(new BlogusergroupObject(*other.d))
{ }

Blogusergroup::Blogusergroup(const BlogusergroupObject &object)
    : TAbstractModel(), d(new BlogusergroupObject(object))
{ }

Blogusergroup::~Blogusergroup()
{
    // If the reference count becomes 0,
    // the shared data object 'BlogusergroupObject' is deleted.
}

int Blogusergroup::id() const
{
    return d->id;
}

int Blogusergroup::usergroupid() const
{
    return d->usergroupid;
}

void Blogusergroup::setUsergroupid(int usergroupid)
{
    d->usergroupid = usergroupid;
}

int Blogusergroup::bloggroupid() const
{
    return d->bloggroupid;
}

void Blogusergroup::setBloggroupid(int bloggroupid)
{
    d->bloggroupid = bloggroupid;
}

QString Blogusergroup::createdAt() const
{
    return d->created_at;
}

QString Blogusergroup::updatedAt() const
{
    return d->updated_at;
}

Blogusergroup &Blogusergroup::operator=(const Blogusergroup &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Blogusergroup Blogusergroup::create(int usergroupid, int bloggroupid)
{
    BlogusergroupObject obj;
    obj.usergroupid = usergroupid;
    obj.bloggroupid = bloggroupid;
    if (!obj.create()) {
        return Blogusergroup();
    }
    return Blogusergroup(obj);
}

Blogusergroup Blogusergroup::create(const QVariantMap &values)
{
    Blogusergroup model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Blogusergroup Blogusergroup::get(int id)
{
    TSqlORMapper<BlogusergroupObject> mapper;
    return Blogusergroup(mapper.findByPrimaryKey(id));
}

int Blogusergroup::count()
{
    TSqlORMapper<BlogusergroupObject> mapper;
    return mapper.findCount();
}

QList<Blogusergroup> Blogusergroup::getAll()
{
    return tfGetModelListByCriteria<Blogusergroup, BlogusergroupObject>(TCriteria());
}

QJsonArray Blogusergroup::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<BlogusergroupObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<BlogusergroupObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Blogusergroup(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Blogusergroup::modelData()
{
    return d.data();
}

const TModelObject *Blogusergroup::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Blogusergroup &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Blogusergroup &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Blogusergroup)
