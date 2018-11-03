#include <QtCore>
#include <TreeFrogView>
#include "user.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT user_userregisterView : public TActionView
{
  Q_OBJECT
public:
  user_userregisterView() : TActionView() { }
  QString toString();
};

QString user_userregisterView::toString()
{
  responsebody.reserve(3224);
  tfetch(QVariantMap,user);
  responsebody += QLatin1String("<!doctype html>\r\n");
    responsebody += QLatin1String("<html lang=\"zh-CN\">\r\n  <head>\r\n    <!-- Required meta tags -->\r\n    <meta charset=\"utf-8\">\r\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">\r\n    <!-- Bootstrap CSS -->\r\n    <link rel=\"stylesheet\" href=\"/css/bootstrap/bootstrap.min.css\">\r\n    <title>");
  eh(controller()->name() + " " + controller()->activeAction());
  responsebody += tr("</title>\r\n  </head>\r\n  <body>\r\n    <div class=\"mynavbar\"></div>\r\n    <div class=\"container\">\r\n        <p class=\"h1 text-dark\">用户注册</p>\r\n    </div>\r\n    <div class=\"alert alert-danger alert-dismissible fade show\" id=\"notice_bar\">\r\n        <p id=\"notice\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\r\n        <button class=\"close\" data-dismisse=\"alert\" aria-label=\"close\">\r\n            <span aria-hidden=\"true\">x</span>\r\n        </button>\r\n    </div>\r\n    <form ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<form action=\"post\" method=\"post\">\r\n        "), (formTag(urla("userregister")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("<div class=\"form-group\">\r\n            <label for=\"username\">用户名： </label>\r\n            <input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input type=\"text\" class=\"form-control\" id=\"username\">\r\n            "), (inputTextTag("user[name]",user["name"]))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("<label for=\"password\">密码: </label>\r\n            <input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input type=\"text\" class=\"form-control\" id=\"password\">\r\n        "), (inputPasswordTag("user[password]",user["password"]))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("</div>\r\n        <div class=\"form-group\">\r\n            <label for=\"email\">邮箱: </label>\r\n            <input type=\"email\" class=\"form-control\" id=\"email\">\r\n            <div class=\"fade show\">\r\n                <form action=\"\" method=\"post\"></form>\r\n            </div>\r\n        </div>\r\n\r\n    </form>\r\n\r\n    <!-- Optional JavaScript -->\r\n    <!-- jQuery first, then Popper.js, then Bootstrap JS -->\r\n    <script src=\"/js/bootstrap/jquery-3.3.1.min.js\"></script>\r\n    <script src=\"/js/bootstrap/popper.min.js\"></script>\r\n    <script src=\"/js//bootstrap/bootstrap.min.js\"></script>\r\n    <script src=\"/js/mysetting/navbar.js\"></script>\r\n    <script>\r\n        $(document).ready(function(){\r\n            $(\"#i_login\").addClass(\"active\");\r\n            if($(\"#notice\").text().length==0){\r\n                $(\"#notice_bar\").hide();\r\n            }\r\n        })\r\n    </script>\r\n  </body>\r\n</html>");

  return responsebody;
}

T_DEFINE_VIEW(user_userregisterView)

#include "user_userregisterView.moc"
