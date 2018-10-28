#include <QtCore>
#include <TreeFrogView>
#include "blog.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blog_createView : public TActionView
{
  Q_OBJECT
public:
  blog_createView() : TActionView() { }
  QString toString();
};

QString blog_createView::toString()
{
  responsebody.reserve(3127);
  tfetch(QVariantMap, blog);
  responsebody += QLatin1String("<!DOCTYPE html>\r\n");
    responsebody += QLatin1String("<html>\r\n<head>\r\n  <meta charset=\"UTF-8\">\r\n  <title>");
  eh(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\r\n   <link rel=\"stylesheet\" href=\"/css/bootstrap/bootstrap.min.css\">\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += tr("</p>\r\n <div class=\"mynavbar\"></div>\r\n<div class=\"container\">\r\n  <p class=\"h1 bg-transparent text-dark\"> 创建博客: </p>\r\n</div>\r\n<div class=\"container-fluid\">\r\n\r\n  <form ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<form method=\"POST\">\r\n  "), (formTag(urla("create")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("<div class=\"form-group\">\r\n    <label> 标题 </label>\r\n    <input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input class=\"form-control\" />"), (inputTextTag("blog[title]", blog["title"].toString()))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(" />");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("  </div>\r\n  <div class=\"form-group\">\r\n    <label>正文</label>\r\n    <input type=\"file\" class=\"form-control-file\" id=\"inputfile\">\r\n    <small class=\"form-text form-muted\"> 键盘输入或者打开文本文件</small>\r\n    <textarea ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<textarea class=\"form-control\" id=\"inputtext\">"), (textAreaTag("blog[body]", 20,100,blog["body"].toString()))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("</textarea>\r\n  </div>\r\n  <div class=\"btn-group\">\r\n    <input type=\"submit\" class=\"btn btn-primary md-2\" value=\"创建博客\" />\r\n    <a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a class=\"btn btn-light\" href=\"#\">返回"), (linkTo("返回", urla("index")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a>\r\n  </div>\r\n</form>\r\n</div>\r\n\r\n<script src=\"/js/bootstrap/jquery-3.3.1.min.js\"></script>\r\n<script src=\"/js/bootstrap/popper.min.js\"></script>\r\n<script src=\"/js//bootstrap/bootstrap.min.js\"></script>\r\n<script src=\"/js/mysetting/navbar.js\"></script>\r\n<script>\r\n  $(\"#inputfile\").change(function(){\r\n    var reader =  new FileReader()\r\n    reader.readAsText($(\"#inputfile\").get(0).files[0]);\r\n    reader.onloadend =function(){\r\n      $(\"#inputtext\").val(reader.result);\r\n    };\r\n  })\r\n  $(document).ready(function(){\r\n    $(\"#i_blog\").addClass(\"active\");\r\n  })\r\n  </script>\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

T_DEFINE_VIEW(blog_createView)

#include "blog_createView.moc"
