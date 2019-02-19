#include "RDSSync.h"
#include<elastic.h>
#include<qdatetime.h>
#define SAVE_FAILED(x)  tDebug("synchronous table failed! query: %s ; message: %s ; ",x.lastQuery().toUtf8().constData(),x.lastError().text().toUtf8().constData())
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(plugin, Sync2Elatic)
#endif // QT_VERSION < 0x050000
Sync2Elatic::Sync2Elatic(){ 
	tDebug("create Plugin Plugin.RDSSync.Elastic"); 
}
void Sync2Elatic::job()
{
	QMutexLocker locker(&mutex);
	if (second > 100000000) {
		second -= 100000000;
	}
	sync2Elastic();
}

void Sync2Elatic::sync2Elastic() {
	try {
		Tf::currentSqlDatabase(0);
		TSqlQuery query(0); 
		tDebug("Start synchronous table");
		if (!query.exec(QString("select tablename,time_index_name,last_sync_time,period,databaseid,result,mainkey from %1").arg(synctablename))) {  //! 获取所有需要同步的表
			SAVE_FAILED(query);
			return;
		}
		QSqlRecord record = query.record();
		QDateTime nowtime = QDateTime::currentDateTime();
		Q_ASSERT(record.count()==7&&record.fieldName(0) == "tablename"&&record.fieldName(1) == "time_index_name"&&record.fieldName(2) == "last_sync_time"&&record.fieldName(3) == "period"&&record.fieldName(4) == "databaseid"&&record.fieldName(5) == "result"&&record.fieldName(6) == "mainkey");
		//开始同步
		while (query.next()) {// 同步一个表
			if (query.value(2).toDateTime().secsTo(nowtime) <= query.value(3).toInt()) { // 如果表的周期未到，则跳过
				continue;
			}
			QJsonDocument allresults = QJsonDocument::fromBinaryData(query.value(5).toByteArray());//数据库中获取的同步结果JSON
			if (allresults.isNull()||!allresults.isObject()) {
				allresults.setObject(QJsonObject());
			}
			auto results = allresults.object();//结果object
			tDebug("On synchronous table %s", query.value(0).toByteArray().constData());
			TSqlQuery syncquery(query.value(4).toInt());
			QString databasename = Tf::currentSqlDatabase(query.value(4).toInt()).databaseName(),tablename = query.value(0).toString();
			databasename  =  databasename.split(QRegExp("[/\\\\]")).last();
			syncquery.prepare(QString("select * from %1 where %2>:last_sync_time and %2<=:nowtime").arg(tablename).arg(query.value(1).toString())).bind(":last_sync_time",query.value(2)).bind(":nowtime", nowtime);
			if (!syncquery.exec()) {
				SAVE_FAILED(syncquery);
				continue;
			}
			auto syncrecord = syncquery.record();
			QString mainkey = query.value(6).toString();
			QStringList keys ;
			for (int i = 0;i < syncrecord.count(); ++i) {// 获取表的所有键
				keys.append(syncrecord.fieldName(i));
			}
			tDebug("keys contains: %s", keys.join(';').toStdString().c_str());
			int indexid = syncrecord.indexOf(mainkey);
			if (indexid == -1) {
				tError("synchronous table %s failed! the time_index_name \"%s\" didn't find", tablename.toStdString().c_str(), query.value(1).toString().toStdString().c_str());
				continue;
			}
			while (syncquery.next()) {//同步表的一条记录
				QJsonObject doc;   
				for (int i = 0; i < keys.count(); ++i) {
					doc[keys[i]] = syncquery.value(i).toJsonValue();// 保存记录到json
				}
				QString url = QString("%1/%2-%3/%3/%4").arg(serverurl).arg(databasename).arg(tablename).arg(syncquery.value(indexid).toString());			
				auto result = Elastic::Put(url, QJsonDocument(doc));//保存记录到Elasticsearch服务器
				tDebug("request %s result is %s", qPrintable(url), qPrintable(result.toJson(QJsonDocument::Compact)));
				if (result.isObject()) {
					auto obj = result.object();
					if (!obj.contains("result")) {
						if (obj.contains("status")) {
							if (obj["status"].isDouble()) {
								auto status = obj["status"].toInt();
								switch (status)
								{
								case 201:
									obj["result"] = QJsonValue("created");
									result.setObject(obj);
									break;
								case 403:
									break;
								default:
									continue;
								}
							}
							else {
								continue;
							}
						}
						else {
							continue;
						}	
					}
					results[syncquery.value(indexid).toString()] = result["result"];    // 保存结果				
				}
			   
			}
			TSqlQuery saveresult; 
			saveresult.prepare(QString("update %1 set result =:result,last_sync_time=:last_index where tablename='%2'").arg(synctablename).arg(tablename)).bind(":result", QJsonDocument(results).toBinaryData()).bind(":result", QJsonDocument(results).toBinaryData()).bind(":last_index", nowtime);
			if (!saveresult.exec()) {
				SAVE_FAILED(saveresult);
				return;
			}
			tInfo("sync table %s in database %s result %s",tablename.toUtf8().constData(), databasename.toUtf8().constData(),QJsonDocument(results).toJson(QJsonDocument::Compact).constData());
		}
		tDebug("End synchronous table");
	}
	catch (QException ex) {
		tDebug("unknow error in %s , Error MSG: %s", __FUNCTION__, ex.what());
	}
}
bool Sync2Elatic::add(const QString& table,const QString &index_name, const QString &  mainkey,int second,int databaseid) {
	QMutexLocker locker(&mutex);
	TSqlQuery query(0);
	try {
		Q_ASSERT(second > 0);
		if (!query.exec(QString("select * from %2 where tablename='%1'").arg(table).arg(synctablename))) { //! 查询同步表是否已经存在
			SAVE_FAILED(query);
			return false;
		}
		auto record = query.record();
		Q_ASSERT(record.count()==7&&record.fieldName(0) == "tablename"&&record.fieldName(1) == "time_index_name"&&record.fieldName(2) == "last_sync_time"&&record.fieldName(3) == "period"&&record.fieldName(4) == "databaseid"&&record.fieldName(5) == "result"&&record.fieldName(6) == "mainkey");
		if (!query.next()) {//! 如果同步表不存在则创建
			query.finish();
			query.prepare(QString("insert into %1 (tablename,time_index_name,last_sync_time ,period,databaseid,mainkey) values(:table,:index_name,:time,:second,:databaseid,:mainkey)").arg(synctablename)).bind(":table", table).bind(":index_name", index_name).bind(":time", QDateTime::fromSecsSinceEpoch(0)).bind(":second", second).bind(":databaseid", databaseid).bind(":mainkey", mainkey);
			if (!query.exec()) {
				SAVE_FAILED(query);
				return false;
			}
			tDebug("insert %s to %s success!", table.toStdString().c_str(), synctablename.toStdString().c_str());
		}
		else {
			if (query.value(3).toInt() != second || query.value(1).toString()!= index_name|| query.value(4).toInt() != databaseid||query.value(6)!= mainkey) { //!如果已经存在同步表，则判断是否需要更新
				query.finish();
				query.prepare(QString("update %1 set period=:period,time_index_name=:time_index_name,databaseid=:databaseid,mainkey=:mainkey where tablename='%2'").arg(synctablename).arg(table)).bind(":period", second).bind(":time_index_name", index_name).bind(":databaseid", databaseid).bind(":mainkey", mainkey);
				tDebug("bind values %s, query.",qPrintable(QJsonDocument::fromVariant(query.boundValues()).toJson(QJsonDocument::Compact)));
				if (!query.exec()) { //更新同步表
					SAVE_FAILED(query);
					return false;
				}
				tDebug("update %s to %s success!", table.toStdString().c_str(), synctablename.toStdString().c_str());
			}
			
		}
		return true;
	}
	catch (QException ex) {
		tDebug("unknow error in %s , Error MSG: %s", __FUNCTION__, ex.what());
	}
	return false;
}

bool Sync2Elatic::remove(const QString & table)
{
	QMutexLocker locker(&mutex);
	try {
		TSqlQuery query(0);
		if (!query.exec(QString("delete from $2 where tablename='%1'").arg(table).arg(synctablename))) {
			SAVE_FAILED(query);
			return false;
		}
	}
	catch (QException ex) {
		tDebug("unknow error in %s , Error MSG: %s", __FUNCTION__, ex.what());
		return false;
	}
	return true;
}

void Sync2Elatic::setConfig(const QVariantMap& setting) {
	auto keys = setting.keys();
	for (auto it = keys.begin(); it != keys.end(); ++it) {
		if (*it == "serverurl") {
			serverurl = setting[*it].toString();
		}
		else if (*it == "tablename") {
			synctablename = setting[*it].toString();
		}
	}
}

void Sync2Elatic::sync()
{
	start(1000);
}

bool Sync2Elatic::release()
{
	setAutoDelete(true);
	stop();
	return false;
}
