#include "usercontroller.h"
#include "informationmailer.h"
#include "user.h"
#pragma execution_character_set("utf-8") 


void UserController::login()
{
    switch(httpRequest().method()){
    case Tf::Get:
		InformationMailer().send("hybtalented@163.com", "hello from hybtalented");
        render();
        break;
    case Tf::Post:
        auto userdata = httpRequest().formItems("user");
        auto user = User::authenticate(userdata["name"].toString(),userdata["password"].toString());
        if(!user.count()){
            QString notice=QString("用户名不存在或密码错误。");
            texport(notice);
            render();
        }else{
            QString notice=QString("Welcome ")+ user.username() ;
        }
    }
    // write code
}

void UserController::userregister()
{
    // write code
    switch(httpRequest().method()){
        case Tf::Get:
			
            render();
            break;
    }
}

void UserController::logout()
{
    // write code
}

// Don't remove below this line
T_DEFINE_CONTROLLER(UserController)
