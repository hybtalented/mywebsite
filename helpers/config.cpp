#include "config.h"
#include<qconfig.h>
#include<qsqlquery.h>
#include<tsqlquery.h>
QString Config::getConfig(const QString & name)
{
	TSqlQuery query;
	if (!query.exec(QString("select name,value from %1 where name='%2'").arg(CONFIG_TABLE_NAME).arg(name))) {
		tError("%s failed!Config:%s. Error:%s", __FUNCTION__,name,query.lastError().text().toUtf8().constData());
	}
	if (query.next()) {
		return query.value(1).toString();
	}
	return QString();
}
