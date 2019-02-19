#include "sqlsynchelper.h"
#include<qpluginloader.h>
#include<qfile.h>
#include<qdir.h>
#include"config.h"
#include<syncplugin.h>
#include<qlibraryinfo.h>
SyncInterface * SqlSyncHelper::syncobj = nullptr;
void SqlSyncHelper::sync()
{
	if (!syncobj && !getPlugin()) {
		tDebug("%s failed! Sync Plugin did't initialize properly", __FUNCTION__);
		return;
	}
	syncobj->sync();
}


bool SqlSyncHelper::add(const QString & table, const QString & index_name, const QString &  mainkey, int second, int databaseid)
{
	if (!syncobj && !getPlugin()) {
		tDebug("%s failed! Sync Plugin did't initialize properly", __FUNCTION__);
		return false;
	}
	return syncobj->add(table, index_name,mainkey, second, databaseid);
}

bool SqlSyncHelper::remove(const QString & table)
{
	if (!syncobj && !getPlugin()) {
		tDebug("%s failed! Sync Plugin did't initialize properly", __FUNCTION__);
		return false;
	}
	return syncobj->remove(table); ;
}

void SqlSyncHelper::release()
{
	if (syncobj) {
		if (syncobj->release()) {
			delete syncobj;
		}
		syncobj = nullptr;
	}
}

bool SqlSyncHelper::getPlugin()
{
	if (!syncobj) {
		QString pluginpath = QDir::currentPath()+"/plugin/lib/RDSSync.dll";
		QFile file(pluginpath);
		if (!file.exists()) {
			tDebug("load plugin RDSSync failed! Path: %s not exist", pluginpath.toUtf8().constData());
			return false;
		}
		QPluginLoader loader(pluginpath);
		QObject *instance = loader.instance();
		if (instance != nullptr) {
			syncobj = qobject_cast<SyncInterface*>(instance);
			QVariantMap setting;
#if defined(_DEBUG)
			setting.insert("serverurl", "http:\/\/47.110.71.66:9200");
#else
			setting.insert("serverurl", Config::getConfig("elastic.serverurl"));
#endif
			setting.insert("tablename", Config::getConfig("elastic.tablename"));
			syncobj->setConfig(setting);
			if (!syncobj) {
				tDebug("load plugin RDSSync failed! Cast instance to SyncInterface with error!");
				return false;
			}
			return true;
		}
		else {
			tInfo("load plugin RDSSync failed!");
			return false;
		}
	}
	return true;
}
