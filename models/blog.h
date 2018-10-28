#ifndef BLOG_H
#define BLOG_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class BlogObject;
class QJsonArray;


class T_MODEL_EXPORT Blog : public TAbstractModel
{
public:
    Blog();
    Blog(const Blog &other);
    Blog(const BlogObject &object);
    ~Blog();

    int id() const;
    QString title() const;
    void setTitle(const QString &title);
    QString body() const;
    void setBody(const QString &body);
    QString createdAt() const;
    QString updatedAt() const;
    int lockRevision() const;
    Blog &operator=(const Blog &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Blog create(const QString &title, const QString &body);
    static Blog create(const QVariantMap &values);
    static Blog get(int id);
    static Blog get(int id, int lockRevision);
    static int count();
    static QList<Blog> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<BlogObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Blog &model);
    friend QDataStream &operator>>(QDataStream &ds, Blog &model);
};

Q_DECLARE_METATYPE(Blog)
Q_DECLARE_METATYPE(QList<Blog>)

#endif // BLOG_H
