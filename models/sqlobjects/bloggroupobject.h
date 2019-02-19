#ifndef BLOGGROUPOBJECT_H
#define BLOGGROUPOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT BloggroupObject : public TSqlObject, public QSharedData
{
public:
    int groupid {0};
    QString groupname;
    int blogid {0};
    QString created_at;
    QString updated_at;

    enum PropertyIndex {
        Groupid = 0,
        Groupname,
        Blogid,
        CreatedAt,
        UpdatedAt,
    };

    int primaryKeyIndex() const override { return Groupid; }
    int autoValueIndex() const override { return Groupid; }
    QString tableName() const override { return QLatin1String("bloggroup"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int groupid READ getgroupid WRITE setgroupid)
    T_DEFINE_PROPERTY(int, groupid)
    Q_PROPERTY(QString groupname READ getgroupname WRITE setgroupname)
    T_DEFINE_PROPERTY(QString, groupname)
    Q_PROPERTY(int blogid READ getblogid WRITE setblogid)
    T_DEFINE_PROPERTY(int, blogid)
    Q_PROPERTY(QString created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QString, created_at)
    Q_PROPERTY(QString updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QString, updated_at)
};

#endif // BLOGGROUPOBJECT_H
