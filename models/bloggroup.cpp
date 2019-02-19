#include <TreeFrogModel>
#include "bloggroup.h"
#include "bloggroupobject.h"

Bloggroup::Bloggroup()
    : TAbstractModel(), d(new BloggroupObject())
{
    d->groupid = 0;
    d->blogid = 0;
}

Bloggroup::Bloggroup(const Bloggroup &other)
    : TAbstractModel(), d(new BloggroupObject(*other.d))
{ }

Bloggroup::Bloggroup(const BloggroupObject &object)
    : TAbstractModel(), d(new BloggroupObject(object))
{ }

Bloggroup::~Bloggroup()
{
    // If the reference count becomes 0,
    // the shared data object 'BloggroupObject' is deleted.
}

int Bloggroup::groupid() const
{
    return d->groupid;
}

QString Bloggroup::groupname() const
{
    return d->groupname;
}

void Bloggroup::setGroupname(const QString &groupname)
{
    d->groupname = groupname;
}

int Bloggroup::blogid() const
{
    return d->blogid;
}

void Bloggroup::setBlogid(int blogid)
{
    d->blogid = blogid;
}

QString Bloggroup::createdAt() const
{
    return d->created_at;
}

QString Bloggroup::updatedAt() const
{
    return d->updated_at;
}

Bloggroup &Bloggroup::operator=(const Bloggroup &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Bloggroup Bloggroup::create(const QString &groupname, int blogid)
{
    BloggroupObject obj;
    obj.groupname = groupname;
    obj.blogid = blogid;
    if (!obj.create()) {
        return Bloggroup();
    }
    return Bloggroup(obj);
}

Bloggroup Bloggroup::create(const QVariantMap &values)
{
    Bloggroup model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Bloggroup Bloggroup::get(int groupid)
{
    TSqlORMapper<BloggroupObject> mapper;
    return Bloggroup(mapper.findByPrimaryKey(groupid));
}

int Bloggroup::count()
{
    TSqlORMapper<BloggroupObject> mapper;
    return mapper.findCount();
}

QList<Bloggroup> Bloggroup::getAll()
{
    return tfGetModelListByCriteria<Bloggroup, BloggroupObject>(TCriteria());
}

QJsonArray Bloggroup::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<BloggroupObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<BloggroupObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Bloggroup(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Bloggroup::modelData()
{
    return d.data();
}

const TModelObject *Bloggroup::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Bloggroup &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Bloggroup &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Bloggroup)
