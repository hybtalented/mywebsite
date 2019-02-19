#ifndef RDSSYNC_H
#define RDSSYNC_H
#include <qobject.h>
#include<tsqlobject.h>
#include<qtimer.h>
#include <tsqlquery.h>
#include<qthread.h>
#include<tscheduler.h>
#include"../syncplugin.h"
class Sync2Elatic:public TScheduler,public SyncInterface{
	Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	Q_INTERFACES(SyncInterface)
	Q_PLUGIN_METADATA(IID "Plugin.RDSSync.Elastic")
#endif
public:
	Sync2Elatic();
	void sync();
	bool add(const QString& table, const QString &index_name, const QString &  mainkey, int second=10, int databaseid = 0)override;
	bool remove(const QString& table)override;
	void setConfig(const QVariantMap&)override;
	bool release()override;
	~Sync2Elatic() { tDebug("Plugin.RDSSync.Elastic has been destroyed;"); }
public slots:
	void sync2Elastic();
	void job()override;
signals:
	void startTimer();
private:
	int second{ 0 };
	QMutex mutex;
	QString synctablename;
	QString  serverurl;
};
#endif