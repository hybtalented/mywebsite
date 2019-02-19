#ifndef ELASTIC_H
#define ELASTIC_H

#include <TGlobal>
#include "applicationhelper.h"
#include<qbuffer>
class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;
class T_HELPER_EXPORT Elastic : public ApplicationHelper
{
public:
	static QJsonDocument Put(const QString& url,const QJsonDocument& query_string);
	static QJsonDocument Get(const QString& url, const QJsonDocument& query_string);
	static QJsonDocument Post(const QString& url, const QJsonDocument& query_string);
	static QNetworkReply* Head(const QString& url, const QJsonDocument& query_string);
	static QJsonDocument Delete(const QString& url, const QJsonDocument& query_string);
	static QNetworkReply* Send(const QNetworkRequest&, const QString&method, QByteArray & body);
private:
	
};

#endif // ELASTIC_H
