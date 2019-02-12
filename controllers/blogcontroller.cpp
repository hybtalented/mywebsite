#include "blogcontroller.h"
#include "blog.h"
#include<tsqlquery.h>
#include <groups.h>
#include"usercontroller.h"
void BlogController::index()
{
    auto blogList = Blog::getAll();
    texport(blogList);
    render();
}

void BlogController::show(const QString &id)
{
    auto blog = Blog::get(id.toInt());
    texport(blog);
    render();
}
void BlogController::share(const QString &id)
{
    auto blog = Blog::get(id.toInt());
    texport(blog);
    render();
}

void BlogController::getblog()
{
	const TSession& sess = session();
	QJsonArray  bloglist;
	if (UserController::isUserLogin(sess)) {
		QString username = sess.value("username").toString();
		
		
	}


}

void BlogController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto blog = httpRequest().formItems("blog");
        auto model = Blog::create(blog);

        if (!model.isNull()) {
            QString notice = "博客创建成功。";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "无法创建博客。";
            texport(error);
            texport(blog);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void BlogController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = Blog::get(id.toInt());
        if (!model.isNull()) {
            session().insert("blog_lockRevision", model.lockRevision());
            auto blog = model.toVariantMap();
            texport(blog);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        int rev = session().value("blog_lockRevision").toInt();
        auto model = Blog::get(id.toInt(), rev);
        
        if (model.isNull()) {
            error = u8"博客保存失败，可能已被删除或被他人更改.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }
        auto blog = httpRequest().formItems("blog");
        model.setProperties(blog);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(blog);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void BlogController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto blog = Blog::get(id.toInt());
    blog.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(BlogController)
