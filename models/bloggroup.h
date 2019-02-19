#ifndef BLOGGROUP_H
#define BLOGGROUP_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class BloggroupObject;
class QJsonArray;


class T_MODEL_EXPORT Bloggroup : public TAbstractModel
{
public:
    Bloggroup();
    Bloggroup(const Bloggroup &other);
    Bloggroup(const BloggroupObject &object);
    ~Bloggroup();

    int groupid() const;
    QString groupname() const;
    void setGroupname(const QString &groupname);
    int blogid() const;
    void setBlogid(int blogid);
    QString createdAt() const;
    QString updatedAt() const;
    Bloggroup &operator=(const Bloggroup &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Bloggroup create(const QString &groupname, int blogid);
    static Bloggroup create(const QVariantMap &values);
    static Bloggroup get(int groupid);
    static int count();
    static QList<Bloggroup> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<BloggroupObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Bloggroup &model);
    friend QDataStream &operator>>(QDataStream &ds, Bloggroup &model);
};

Q_DECLARE_METATYPE(Bloggroup)
Q_DECLARE_METATYPE(QList<Bloggroup>)

#endif // BLOGGROUP_H
