#include "applicationcontroller.h"
#include<sqlsynchelper.h>
#include<qdir.h>
ApplicationController::ApplicationController()
    : TActionController()
{ }

ApplicationController::~ApplicationController()
{ }

void ApplicationController::staticInitialize()
{
	//！ 初始化插件加载路径和同步表	
	const bool result = SqlSyncHelper::add("blog", "updated_at","id" ,5);
	SqlSyncHelper::sync();
	tDebug("Sync setting finished!");
}

void ApplicationController::staticRelease()
{
	tDebug("In %s start", __FUNCTION__);
	SqlSyncHelper::release();
	tDebug("%s", __FUNCTION__);
}

bool ApplicationController::preFilter()
{
    return true;
}

// Don't remove below this line
T_DEFINE_CONTROLLER(ApplicationController)
