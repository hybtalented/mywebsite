#include <QtCore>
#include <TreeFrogView>
#include "blog.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blog_indexView : public TActionView
{
  Q_OBJECT
public:
  blog_indexView() : TActionView() { }
  QString toString();
};

QString blog_indexView::toString()
{
  responsebody.reserve(3290);
  responsebody += QLatin1String("<!DOCTYPE html>\r\n");
    responsebody += QLatin1String("<html>\r\n<head>\r\n  <meta charset=\"UTF-8\">\r\n  <title>");
  eh(controller()->name() + ": " + controller()->activeAction());
  responsebody += tr("</title>\r\n  <link rel=\"stylesheet\" href=\"/css/bootstrap/bootstrap.min.css\">\r\n</head>\r\n<body>\r\n <div class=\"mynavbar\"></div>\r\n\r\n <div class=\"container\">\r\n   <p class=\"h1 bg-transparent text-dark\">博客列表</p>\r\n</div>\r\n\r\n<div class=\"alert alert-info\">\r\n  <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a href=\"#\">创建博客"), (linkTo("创建新的博客!", urla("create")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("</a><br />\r\n\r\n</div>\r\n<br />\r\n<table border=\"1\" cellpadding=\"5\" class=\"table table-hover\" style=\"border: 1px #d0d0d0 solid; border-collapse: collapse;\">\r\n  <thead class=\"thead-dark\">\r\n    <tr>\r\n      <th scope=\"col\">用户ID</th>\r\n      <th scope=\"col\">标题</th>\r\n      <th scope=\"col\">内容</th>\r\n      <th scope=\"col\">操作</th>\r\n      <th></th>\r\n    </tr>\r\n  </thead>\r\n  <th scope=\"row\"></th>\r\n    ");
  tfetch(QList<Blog>, blogList);
for (const auto &i : blogList) {
  responsebody += QLatin1String("<tr>\r\n      <td>");
  eh(i.id());
  responsebody += QLatin1String("</td>\r\n      <td>");
  eh(i.title());
  responsebody += QLatin1String("</td>\r\n      <td><textarea readonly=\"readonly\">");
  eh(i.body());
  responsebody += QLatin1String("</textarea></td>\r\n      <td>\r\n        <div class=\"btn-group\">\r\n          <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a href=\"#\" class=\"btn btn-primary\">详情"), (linkTo("详情", urla("show", i.id())))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a>\r\n          <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a href=\"#\" class=\"btn btn-success\">编辑"), (linkTo("编辑", urla("save", i.id())))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a>\r\n          <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a href=\"#\" class=\"btn btn-danger\">删除"), (linkTo("删除", urla("remove", i.id()), Tf::Post, "confirm('Are you sure?')"))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a>\r\n        </div>\r\n    </td>\r\n  </tr>");
  };
  responsebody += QLatin1String("</table>\r\n    <script src=\"/js/bootstrap/jquery-3.3.1.min.js\"></script>\r\n    <script src=\"/js/bootstrap/popper.min.js\"></script>\r\n    <script src=\"/js//bootstrap/bootstrap.min.js\"></script>\r\n    <script src=\"/js/mysetting/navbar.js\"></script>\r\n    <script>\r\n        $(document).ready(function(){\r\n            $(\"#i_login\").addClass(\"active\");\r\n        })\r\n    </script>\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

T_DEFINE_VIEW(blog_indexView)

#include "blog_indexView.moc"
