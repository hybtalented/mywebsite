#ifndef SQLSYNCHELPER_H
#define SQLSYNCHELPER_H

#include <TGlobal>
#include "applicationhelper.h"
class SyncInterface;
class T_HELPER_EXPORT SqlSyncHelper : public ApplicationHelper
{
public:
	static void sync();
	static bool add(const QString& table, const QString &index_name, const QString &  mainkey, int second=10, int databaseid =0);
	static bool remove(const QString& table);
	static void release();
private:
	static bool getPlugin();
	static SyncInterface* syncobj;
};

#endif // SQLSYNCHELPER_H
