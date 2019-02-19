#ifndef USERGROUP_H
#define USERGROUP_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class UsergroupObject;
class QJsonArray;


class T_MODEL_EXPORT Usergroup : public TAbstractModel
{
public:
    Usergroup();
    Usergroup(const Usergroup &other);
    Usergroup(const UsergroupObject &object);
    ~Usergroup();

    int id() const;
    QString groupid() const;
    void setGroupid(const QString &groupid);
    QString userid() const;
    void setUserid(const QString &userid);
    QString createdAt() const;
    QString updatedAt() const;
    Usergroup &operator=(const Usergroup &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Usergroup create(const QString &groupid, const QString &userid);
    static Usergroup create(const QVariantMap &values);
    static Usergroup get(int id);
    static int count();
    static QList<Usergroup> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<UsergroupObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Usergroup &model);
    friend QDataStream &operator>>(QDataStream &ds, Usergroup &model);
};

Q_DECLARE_METATYPE(Usergroup)
Q_DECLARE_METATYPE(QList<Usergroup>)

#endif // USERGROUP_H
