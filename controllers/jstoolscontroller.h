#ifndef JSTOOLSCONTROLLER_H
#define JSTOOLSCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT JstoolsController : public ApplicationController
{
    Q_OBJECT
public:
    JstoolsController() : ApplicationController() { }

public slots:
    void base64transfer();
};

#endif // JSTOOLSCONTROLLER_H
