#include "usercontroller.h"
#include "informationmailer.h"
#include "user.h"
#include <qrandom.h>
#include <qexception.h>
#include<qfile.h>
#pragma execution_character_set("utf-8") 
static QRandomGenerator randGen = QRandomGenerator::securelySeeded();
void UserController::index() {
	switch (httpRequest().method())
	{
	case Tf::Get:
		if (isUserLogin(session())) {
			QString notice = QString(u8"欢迎 %1 登陆hybtalented的个人网站").arg(session().value("username").toString());
			tflash(notice);
			render();
		}
		else {
			session().remove("username");
			redirect(urla("login"));
		}
		break;
	default:
		break;
	}
}
void UserController::isLogin() {
	QJsonDocument jsondoc;
	QJsonObject jsonobj;
	THttpResponse& response = httpResponse();
	response.header().setContentType("application/json");
	if ( isUserLogin(session())) {
		jsonobj["login"] = true;
		QString username = session().value("username").toString();
		jsonobj["username"] = username;
		jsonobj["icon"] = QString::fromUtf8(User::get(username).icon().toBase64());
	}
	else {
		jsonobj["login"] = false;
	}
	jsondoc.setObject(jsonobj);
	response.setBody(jsondoc.toJson(QJsonDocument::Compact));
}
bool UserController::isUserLogin(const TSession& sess) {
	auto username = sess.value("username");
	return !username.isNull() && !User::get(username.toString()).isNull();
}
void UserController::login()
{
    switch(httpRequest().method()){
    case Tf::Get:
        render();
        break;
    case Tf::Post:
        auto userdata = httpRequest().formItems("user");
        auto user = User::authenticate(userdata["name"].toString(),userdata["password"].toString());
		if (isUserLogin(session())) {
			QString error = QString(u8"您已经登陆，请退出登陆后重试!");
			tflash(error);
			render();
		}
		else {
			if (user.isNull()) {
				QString error = QString(u8"用户名不存在或密码错误。");
				tflash(error);
				render();
			}
			else {
				session().insert("username", userdata["name"].toString().toUtf8());
				redirect(urla("index"));
			}
		}
       
    }
    // write code
}
void UserController::userregister()
{
    // write code
	QString notice;
    switch(httpRequest().method()){
        case Tf::Get:
			notice = u8"欢迎注册hybtalented的个人网站!";
			tflash(notice);
            render();
            break;
		case Tf::Post:
			try {
				auto body = QJsonDocument::fromJson(httpRequest().rawBody()->readAll()).object();
				auto email = httpRequest().formItemValue("email");
				auto emailcode = httpRequest().formItemValue("emailcode");
				auto savecode = session().value("emailcode").toString();
				auto saveemail = session().value("email").toString();
				QJsonObject user = body["user"].toObject();
				QByteArray icon = QByteArray::fromBase64(user["icon"].toString().toUtf8());
				if (icon.isEmpty()) {
					icon = QByteArray("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");
				}
				if (session().contains("emailcode")) {
					if (emailcode == savecode && savecode.length() == 6) {
						if (saveemail != email || user["name"].toString().isEmpty()) {
							auto createduser = User::create(user["name"].toString(), user["password"].toString(), email, icon);
							QString error = QString(u8"注册失败,用户名 (%2) 或 邮箱地址 (%1) 有误！").arg(email).arg(user["name"].toString());
							texport(email);
							texport(user);
							texport(error);
							render();
							return;
						}
						if (User::get(user["name"].toString()).isNull()) {
							auto createduser = User::create(user["name"].toString(), user["password"].toString(), email, icon);
							if (createduser.isNull()) {
								QString error = QString(u8"注册失败：写入数据库错误,请联系<a href=\"hybtalented@163.com\" >管理员</a>！").arg(user["name"].toString()).arg(email);
								texport(error);
								render();
							}
							else {
								notice = QString(u8"注册成功,你的用户名为 %1,邮箱地址为 %2！").arg(user["name"].toString()).arg(email);
								tflash(notice);
								redirect(urla("login"));
							}
						}
						else {
							texport(email);
							texport(user);
							QString error = u8"注册失败,用户名已存在！";
							texport(error);
							render();
						}
					}
					else {
						texport(email);
						texport(user);
						QString error = u8"注册失败,验证码错误！";
						texport(error);
						render();
					}
				}
				else {
					texport(email);
					texport(user);
					QString error = u8"注册失败,未输入邮箱地址或未发送验证码！";
					texport(error);
					render();
				}
			}
			catch (QException ex) {
				QString error = u8"注册失败,服务器内部错误，请联系<a href=\"hybtalented@163.com\" >管理员</a>！";
				texport(error);
				render();
			}
		    
			break;
    }
}
void UserController::logout()
{
    // write code
	switch (httpRequest().method()) {
	case Tf::Get:
		session().remove("username");
		redirect(urla("index"));
		break;
	default:
		break;
	}
}

void UserController::sendcode() {
	THttpResponse& response = httpResponse();
	switch (httpRequest().method()) {
	case Tf::Post:
		auto email = httpRequest().formItemValue("email");
		quint64 randvalue = randGen.generate64() % 1000000;
		QString emailcode = QString("%1").arg(randvalue,6,10,QLatin1Char('0'));
		session().insert("emailcode", emailcode);
		session().insert("email", email);
		tDebug("Sending code %s to %s",emailcode.toUtf8().constData(),email.toUtf8().constData() );
		QString body = QString(u8"欢迎注册hybtalneted的个人网站!你的验证码为%1。").arg(emailcode);
		InformationMailer().send(email, body, u8"欢迎注册hybtalneted的个人网站");
		response.header().setContentType("application/text");
		response.setBody(QString(u8"验证已发送到%1,请注意查收!").arg(email).toUtf8());
		break;
	}
}
// Don't remove below this line
T_DEFINE_CONTROLLER(UserController)
