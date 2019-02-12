#ifndef BLOGOBJECT_H
#define BLOGOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT BlogObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QString title;
    QString body;
    QString created_at;
    QString updated_at;
    int lock_revision {0};
    int userid {0};
    bool other_r;

    enum PropertyIndex {
        Id = 0,
        Title,
        Body,
        CreatedAt,
        UpdatedAt,
        LockRevision,
        Userid,
        OtherR,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("blog"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString title READ gettitle WRITE settitle)
    T_DEFINE_PROPERTY(QString, title)
    Q_PROPERTY(QString body READ getbody WRITE setbody)
    T_DEFINE_PROPERTY(QString, body)
    Q_PROPERTY(QString created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QString, created_at)
    Q_PROPERTY(QString updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QString, updated_at)
    Q_PROPERTY(int lock_revision READ getlock_revision WRITE setlock_revision)
    T_DEFINE_PROPERTY(int, lock_revision)
    Q_PROPERTY(int userid READ getuserid WRITE setuserid)
    T_DEFINE_PROPERTY(int, userid)
    Q_PROPERTY(bool other_r READ getother_r WRITE setother_r)
    T_DEFINE_PROPERTY(bool, other_r)
};

#endif // BLOGOBJECT_H
