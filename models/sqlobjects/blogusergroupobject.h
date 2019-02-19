#ifndef BLOGUSERGROUPOBJECT_H
#define BLOGUSERGROUPOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT BlogusergroupObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    int usergroupid {0};
    int bloggroupid {0};
    QString created_at;
    QString updated_at;

    enum PropertyIndex {
        Id = 0,
        Usergroupid,
        Bloggroupid,
        CreatedAt,
        UpdatedAt,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("blogusergroup"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(int usergroupid READ getusergroupid WRITE setusergroupid)
    T_DEFINE_PROPERTY(int, usergroupid)
    Q_PROPERTY(int bloggroupid READ getbloggroupid WRITE setbloggroupid)
    T_DEFINE_PROPERTY(int, bloggroupid)
    Q_PROPERTY(QString created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QString, created_at)
    Q_PROPERTY(QString updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QString, updated_at)
};

#endif // BLOGUSERGROUPOBJECT_H
