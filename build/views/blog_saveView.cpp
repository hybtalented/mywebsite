#include <QtCore>
#include <TreeFrogView>
#include "blog.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blog_saveView : public TActionView
{
  Q_OBJECT
public:
  blog_saveView() : TActionView() { }
  QString toString();
};

QString blog_saveView::toString()
{
  responsebody.reserve(3533);
  tfetch(QVariantMap, blog);
  responsebody += QLatin1String("<!DOCTYPE html>\r\n");
    responsebody += QLatin1String("<html>\r\n<head>\r\n  <meta charset=\"UTF-8\">\r\n  <title>");
  eh(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\r\n  <link rel=\"stylesheet\" href=\"/css/bootstrap/bootstrap.min.css\">\r\n</head>\r\n<body>\r\n  <div class=\"mynavbar\"></div>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n\r\n<div class=\"container\">\r\n  <h1>修改博客内容</h1>\r\n</div>\r\n\r\n<div class=\"container-fluid\">\r\n\r\n  <form ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<form method=\"post\">\r\n    "), (formTag(urla("save", blog["id"])))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("<div class=\"form-group\">\r\n      <label>编号 </label>\r\n      <input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input class=\"form-control\" />"), (inputTextTag("blog[id]", blog["id"].toString(), a("readonly", "readonly")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(" />");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("    </div>\r\n    <div>\r\n      <label>标题</label>\r\n      <input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input class=\"form-control\" />"), (inputTextTag("blog[title]", blog["title"].toString()))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(" />");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("    </div>\r\n    <div>\r\n      <label>正文 </label>\r\n      <textarea ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<textarea class=\"form-control\" rows=\"10\">"), (textAreaTag("blog[body]", 20,100,blog["body"].toString()))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("</textarea>\r\n    </div>\r\n    <div class=\"btn-group\">\r\n      <input class=\"btn btn-primary\" type=\"submit\" value=\"保存\" />\r\n      <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a class=\"btn btn-info\" href=\"#\">Show"), (linkTo("详情", urla("show", blog["id"])))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a> \r\n      <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a class=\"btn btn-light\" href=\"#\">Back"), (linkTo("后退", urla("index")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a>\r\n    </div>\r\n  </form>\r\n</div>\r\n\r\n<script src=\"/js/bootstrap/jquery-3.3.1.min.js\"></script>\r\n    <script src=\"/js/bootstrap/popper.min.js\"></script>\r\n    <script src=\"/js//bootstrap/bootstrap.min.js\"></script>\r\n    <script src=\"/js/mysetting/navbar.js\"></script>\r\n    <script>\r\n        $(document).ready(function(){\r\n            $(\"#i_login\").addClass(\"active\");\r\n        })\r\n    </script>\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

T_DEFINE_VIEW(blog_saveView)

#include "blog_saveView.moc"
