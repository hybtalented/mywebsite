#include <QtCore>
#include <TreeFrogView>
#include "blog.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blog_showView : public TActionView
{
  Q_OBJECT
public:
  blog_showView() : TActionView() { }
  QString toString();
};

QString blog_showView::toString()
{
  responsebody.reserve(2728);
  tfetch(Blog, blog);
  responsebody += QLatin1String("<!DOCTYPE html>\r\n");
    responsebody += QLatin1String("<html>\r\n<head>\r\n  <meta charset=\"UTF-8\">\r\n  <title>");
  eh(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\r\n   <link rel=\"stylesheet\" href=\"/css/bootstrap/bootstrap.min.css\">\r\n</head>\r\n<body>\r\n  <div class=\"mynavbar\"></div>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<div class=\"container\">\r\n  <h1>博客内容</h1>\r\n</div>\r\n<div class=\"container-fluid\">\r\n    <dl class=\"row\">\r\n      <dt class=\"col-sm-2\">博客ID</dt><dd class=\"col-sm-10\">");
  eh(blog.id());
  responsebody += tr("</dd><br />\r\n      <dt class=\"col-sm-2\">标题</dt><dd class=\"col-sm-10\">");
  eh(blog.title());
  responsebody += tr("</dd><br />\r\n      <dt class=\"col-sm-2\">正文</dt><dd class=\"col-sm-10\"><textarea class=\"form-control\" readonly=\"readonly\" cols=\"100\" rows=\"20\">");
  eh(blog.body());
  responsebody += tr("</textarea></dd><br />\r\n      <dt class=\"col-sm-2\">创建时间</dt><dd class=\"col-sm-10\">");
  eh(blog.createdAt());
  responsebody += tr("</dd><br />\r\n      <dt class=\"col-sm-2\">更新时间</dt><dd class=\"col-sm-10\">");
  eh(blog.updatedAt());
  responsebody += tr("</dd><br />\r\n      <dt class=\"col-sm-2\">修改次数</dt><dd class=\"col-sm-10\">");
  eh(blog.lockRevision());
  responsebody += QLatin1String("</dd><br />\r\n    </dl>\r\n</div>\r\n<div class=\"container-fluid btn-group\">\r\n  <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a href=\"#\" class=\"btn btn-light\">Back"), (linkTo("后退", urla("index")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a>\r\n  <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a class=\"btn btn-primary\" href=\"#\">Edit"), (linkTo("编辑", urla("save", blog.id())))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a> \r\n</div>\r\n<script src=\"/js/bootstrap/jquery-3.3.1.min.js\"></script>\r\n    <script src=\"/js/bootstrap/popper.min.js\"></script>\r\n    <script src=\"/js//bootstrap/bootstrap.min.js\"></script>\r\n    <script src=\"/js/mysetting/navbar.js\"></script>\r\n    <script>\r\n        $(document).ready(function(){\r\n            $(\"#i_login\").addClass(\"active\");\r\n        })\r\n    </script>\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

T_DEFINE_VIEW(blog_showView)

#include "blog_showView.moc"
