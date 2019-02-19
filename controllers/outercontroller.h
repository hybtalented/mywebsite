#ifndef OUTERCONTROLLER_H
#define OUTERCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT OuterController : public ApplicationController
{
    Q_OBJECT
public:
    OuterController() : ApplicationController() { }

public slots:
    void access();
};

#endif // OUTERCONTROLLER_H
