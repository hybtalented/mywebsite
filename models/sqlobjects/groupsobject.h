#ifndef GROUPSOBJECT_H
#define GROUPSOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT GroupsObject : public TSqlObject, public QSharedData
{
public:
    int groupid {0};
    QString groupname;
    QString created_at;
    QString updated_at;
    bool write;
    bool read;
    bool manager;
    QByteArray icon;

    enum PropertyIndex {
        Groupid = 0,
        Groupname,
        CreatedAt,
        UpdatedAt,
        Write,
        Read,
        Manager,
        Icon,
    };

    int primaryKeyIndex() const override { return Groupid; }
    int autoValueIndex() const override { return Groupid; }
    QString tableName() const override { return QLatin1String("groups"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int groupid READ getgroupid WRITE setgroupid)
    T_DEFINE_PROPERTY(int, groupid)
    Q_PROPERTY(QString groupname READ getgroupname WRITE setgroupname)
    T_DEFINE_PROPERTY(QString, groupname)
    Q_PROPERTY(QString created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QString, created_at)
    Q_PROPERTY(QString updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QString, updated_at)
    Q_PROPERTY(bool write READ getwrite WRITE setwrite)
    T_DEFINE_PROPERTY(bool, write)
    Q_PROPERTY(bool read READ getread WRITE setread)
    T_DEFINE_PROPERTY(bool, read)
    Q_PROPERTY(bool manager READ getmanager WRITE setmanager)
    T_DEFINE_PROPERTY(bool, manager)
    Q_PROPERTY(QByteArray icon READ geticon WRITE seticon)
    T_DEFINE_PROPERTY(QByteArray, icon)
};

#endif // GROUPSOBJECT_H
