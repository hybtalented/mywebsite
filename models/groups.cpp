#include <TreeFrogModel>
#include "groups.h"
#include "groupsobject.h"

Groups::Groups()
    : TAbstractModel(), d(new GroupsObject())
{
    d->groupid = 0;
}

Groups::Groups(const Groups &other)
    : TAbstractModel(), d(new GroupsObject(*other.d))
{ }

Groups::Groups(const GroupsObject &object)
    : TAbstractModel(), d(new GroupsObject(object))
{ }

Groups::~Groups()
{
    // If the reference count becomes 0,
    // the shared data object 'GroupsObject' is deleted.
}

int Groups::groupid() const
{
    return d->groupid;
}

QString Groups::groupname() const
{
    return d->groupname;
}

void Groups::setGroupname(const QString &groupname)
{
    d->groupname = groupname;
}

QString Groups::createdAt() const
{
    return d->created_at;
}

QString Groups::updatedAt() const
{
    return d->updated_at;
}

bool Groups::write() const
{
    return d->write;
}

void Groups::setWrite(const bool &write)
{
    d->write = write;
}

bool Groups::read() const
{
    return d->read;
}

void Groups::setRead(const bool &read)
{
    d->read = read;
}

bool Groups::manager() const
{
    return d->manager;
}

void Groups::setManager(const bool &manager)
{
    d->manager = manager;
}

QByteArray Groups::icon() const
{
    return d->icon;
}

void Groups::setIcon(const QByteArray &icon)
{
    d->icon = icon;
}

Groups &Groups::operator=(const Groups &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Groups Groups::create(const QString &groupname, const bool &write, const bool &read, const bool &manager, const QByteArray &icon)
{
    GroupsObject obj;
    obj.groupname = groupname;
    obj.write = write;
    obj.read = read;
    obj.manager = manager;
    obj.icon = icon;
    if (!obj.create()) {
        return Groups();
    }
    return Groups(obj);
}

Groups Groups::create(const QVariantMap &values)
{
    Groups model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Groups Groups::get(int groupid)
{
    TSqlORMapper<GroupsObject> mapper;
    return Groups(mapper.findByPrimaryKey(groupid));
}

int Groups::count()
{
    TSqlORMapper<GroupsObject> mapper;
    return mapper.findCount();
}

QList<Groups> Groups::getAll()
{
    return tfGetModelListByCriteria<Groups, GroupsObject>(TCriteria());
}

QJsonArray Groups::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<GroupsObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<GroupsObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Groups(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Groups::modelData()
{
    return d.data();
}

const TModelObject *Groups::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Groups &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Groups &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Groups)
