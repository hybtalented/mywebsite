#ifndef GROUPS_H
#define GROUPS_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class GroupsObject;
class QJsonArray;


class T_MODEL_EXPORT Groups : public TAbstractModel
{
public:
    Groups();
    Groups(const Groups &other);
    Groups(const GroupsObject &object);
    ~Groups();

    int groupid() const;
    QString groupname() const;
    void setGroupname(const QString &groupname);
    QString createdAt() const;
    QString updatedAt() const;
    bool write() const;
    void setWrite(const bool &write);
    bool read() const;
    void setRead(const bool &read);
    bool manager() const;
    void setManager(const bool &manager);
    QByteArray icon() const;
    void setIcon(const QByteArray &icon);
    Groups &operator=(const Groups &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Groups create(const QString &groupname, const bool &write, const bool &read, const bool &manager, const QByteArray &icon);
    static Groups create(const QVariantMap &values);
    static Groups get(int groupid);
    static int count();
    static QList<Groups> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<GroupsObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Groups &model);
    friend QDataStream &operator>>(QDataStream &ds, Groups &model);
};

Q_DECLARE_METATYPE(Groups)
Q_DECLARE_METATYPE(QList<Groups>)

#endif // GROUPS_H
