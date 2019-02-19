#ifndef BLOGUSERGROUP_H
#define BLOGUSERGROUP_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class BlogusergroupObject;
class QJsonArray;


class T_MODEL_EXPORT Blogusergroup : public TAbstractModel
{
public:
    Blogusergroup();
    Blogusergroup(const Blogusergroup &other);
    Blogusergroup(const BlogusergroupObject &object);
    ~Blogusergroup();

    int id() const;
    int usergroupid() const;
    void setUsergroupid(int usergroupid);
    int bloggroupid() const;
    void setBloggroupid(int bloggroupid);
    QString createdAt() const;
    QString updatedAt() const;
    Blogusergroup &operator=(const Blogusergroup &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Blogusergroup create(int usergroupid, int bloggroupid);
    static Blogusergroup create(const QVariantMap &values);
    static Blogusergroup get(int id);
    static int count();
    static QList<Blogusergroup> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<BlogusergroupObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Blogusergroup &model);
    friend QDataStream &operator>>(QDataStream &ds, Blogusergroup &model);
};

Q_DECLARE_METATYPE(Blogusergroup)
Q_DECLARE_METATYPE(QList<Blogusergroup>)

#endif // BLOGUSERGROUP_H
