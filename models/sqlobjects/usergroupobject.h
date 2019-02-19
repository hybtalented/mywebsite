#ifndef USERGROUPOBJECT_H
#define USERGROUPOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT UsergroupObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QString groupid;
    QString userid;
    QString created_at;
    QString updated_at;

    enum PropertyIndex {
        Id = 0,
        Groupid,
        Userid,
        CreatedAt,
        UpdatedAt,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("usergroup"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString groupid READ getgroupid WRITE setgroupid)
    T_DEFINE_PROPERTY(QString, groupid)
    Q_PROPERTY(QString userid READ getuserid WRITE setuserid)
    T_DEFINE_PROPERTY(QString, userid)
    Q_PROPERTY(QString created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QString, created_at)
    Q_PROPERTY(QString updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QString, updated_at)
};

#endif // USERGROUPOBJECT_H
