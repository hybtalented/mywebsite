#include "usercontroller.h"
#include "informationmailer.h"
#include "user.h"
#include <qrandom.h>
#pragma execution_character_set("utf-8") 
static QRandomGenerator randGen = QRandomGenerator::securelySeeded();
void UserController::index() {
	switch (httpRequest().method())
	{
	case Tf::Get:
		if (isUserLogin()) {
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
	if ( isUserLogin()) {
		jsonobj["login"] = true;
		jsonobj["username"] = session().value("username").toString();
	}
	else {
		jsonobj["login"] = false;
	}
	jsondoc.setObject(jsonobj);
	response.setBody(jsondoc.toJson(QJsonDocument::Compact));
}
bool UserController::isUserLogin() {
	auto sess =session();
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
		if (isUserLogin()) {
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
			auto email = httpRequest().formItemValue("email");
			auto emailcode = httpRequest().formItemValue("emailcode");
			auto savecode = session().value("emailcode").toString();
			auto saveemail = session().value("email").toString();
			QVariantMap user = httpRequest().formItems("user");
			if (session().contains("emailcode")) {	
				if (emailcode == savecode&&savecode.length()==6) {
					if ( saveemail != email||user["name"].toString().isEmpty()) {
						auto createduser = User::create(user["name"].toString(), user["password"].toString(), email);
						QString error = QString(u8"注册失败,用户名 (%2) 或 邮箱地址 (%1) 有误！").arg(email).arg(user["name"].toString());
						texport(email);
						texport(user);
						texport(error);
						render();
						return;
					}
					if (User::get(user["name"].toString()).isNull()) {
						auto createduser =User::create(user["name"].toString(), user["password"].toString(), email);
						if (createduser.isNull()) {
							QString error = QString(u8"注册失败：写入数据库错误,请<a href=\"hybtalented@163.com\" >联系管理员</a>！").arg(user["name"].toString()).arg(email);
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
