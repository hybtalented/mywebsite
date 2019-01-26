#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT UserController : public ApplicationController
{
    Q_OBJECT
public:
    UserController() : ApplicationController() { }
	bool isUserLogin();
public slots:
	void isLogin();
	void index();
    void login();
    void userregister();
    void logout();
	void sendcode();
};

#endif // USERCONTROLLER_H
