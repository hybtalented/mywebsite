#ifndef SYNCPLUGIN_H
#define SYNCPLUGIN_H
#include <qobject.h>
class SyncInterface
{
public:
	virtual void sync() = 0;
	virtual bool add(const QString& table, const QString &index_name, const QString &  mainkey, int second, int databaseid) = 0;
	virtual bool remove(const QString& table) = 0;
	virtual void setConfig(const QVariantMap&)=0;
	virtual bool release() = 0;
};
Q_DECLARE_INTERFACE(SyncInterface,"Plugin.RDSSync.Interface")
#endif // !SYNCPLUGIN_H