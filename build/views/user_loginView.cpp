#include <QtCore>
#include <TreeFrogView>
#include "user.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT user_loginView : public TActionView
{
  Q_OBJECT
public:
  user_loginView() : TActionView() { }
  QString toString();
};

QString user_loginView::toString()
{
  responsebody.reserve(2551);
  tfetch(QString,notice);
    responsebody += QLatin1String("<html>\r\n<header>\r\n    <meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\">\r\n    <title>");
  eh(controller()->name()+" "+controller()->activeAction());
  responsebody += tr("</title>\r\n     <link rel=\"stylesheet\" href=\"/css/bootstrap/bootstrap.min.css\">\r\n</header>\r\n<body>\r\n    <div class=\"mynavbar\"></div>\r\n    <h1>用户登陆</h1>\r\n    <div class=\"alert alert-danger alert-dismissible fade show\" role=\"alert\">\r\n        <p>");
  echo(notice + "前往" + linkTo("注册",urla("userregister")));
  responsebody += QLatin1String("</p>\r\n        <button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"close\">\r\n            <span aria-hidden=\"true\">&times;</span>\r\n        </button>\r\n    </div>\r\n    <form ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<form method=\"post\">\r\n        "), (formTag(urla("login")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("<div class=\"form-group\">\r\n            <label for=\"exampleInputUsename1\">用户名： </label> <input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input class=\"form-control\" placeholder=\"User name\">\r\n        "), (inputTextTag("user[name]",""))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("</div>\r\n        <div class=\"form-group\">\r\n            <label for=\"exampleInputPassword1\">密码: </label> <input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input class=\"form-control\" placeholder=\"password\">\r\n        "), (inputPasswordTag("user[password]",""))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += tr("</div>\r\n            <input class=\"btn btn-primary\" type=\"submit\" value=\"登录\">\r\n       </form> \r\n    <script src=\"/js/bootstrap/jquery-3.3.1.min.js\"></script>\r\n    <script src=\"/js/bootstrap/popper.min.js\"></script>\r\n    <script src=\"/js/bootstrap/bootstrap.min.js\"></script>\r\n    <script src=\"/js/mysetting/navbar.js\"></script>\r\n    <script>\r\n        $(document).ready(function(){\r\n            $(\"#i_login\").addClass(\"active\");\r\n        })\r\n    </script>\r\n</body>\r\n</html>");

  return responsebody;
}

T_DEFINE_VIEW(user_loginView)

#include "user_loginView.moc"
