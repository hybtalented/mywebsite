#include "elastic.h"
#include<thttprequest.h>
#include<qnetworkaccessmanager.h>
#include<qnetworkrequest.h>
#include<qnetworkreply.h>
#include<qthread.h>
#include<qexception.h>
#include<qjsonobject.h>
QJsonDocument Elastic::Put(const QString & url, const QJsonDocument & query_string)
{
	QJsonDocument doc;
	QByteArray body = query_string.toJson();
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setUrl(url);
	QNetworkReply* reply = Send(request, "PUT", body);
	if (!reply) {
		return QJsonDocument();
	}
	QByteArray responsebody = reply->readAll();
	tDebug("response return %s",responsebody.constData());
	doc.fromJson(responsebody);
	reply->deleteLater();
	return doc;
}

QJsonDocument Elastic::Get(const QString & url, const QJsonDocument & query_string)
{
	QJsonDocument doc;
	QByteArray body = query_string.toJson();
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setUrl(url);
	QNetworkReply* reply = Send(request, "GET", body);
	if (!reply) {
		return QJsonDocument();
	}
	QByteArray responsebody = reply->readAll();
	tDebug("response return %s", responsebody.constData());
	doc.fromJson(responsebody);
	reply->deleteLater();
	return doc;
}

QJsonDocument Elastic::Post(const QString & url, const QJsonDocument & query_string)
{
	QJsonDocument doc;
	QByteArray body = query_string.toJson();
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setUrl(url);
	QNetworkReply* reply = Send(request, "POST", body);
	if (!reply) {
		return QJsonDocument();
	}
	QByteArray responsebody = reply->readAll();
	tDebug("response return %s", responsebody.constData());
	doc.fromJson(responsebody);
	reply->deleteLater();
	return doc;
}

QNetworkReply* Elastic::Head(const QString & url, const QJsonDocument & query_string)
{
	QJsonDocument doc;
	QByteArray body = query_string.toJson();
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setUrl(url);
	QNetworkReply* reply = Send(request, "HEAD", body);
	return reply;
}

QJsonDocument Elastic::Delete(const QString & url, const QJsonDocument & query_string)
{
	QJsonDocument doc;
	QByteArray body = query_string.toJson();
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setUrl(url);
	QNetworkReply* reply = Send(request, "DELETE", body);
	if (!reply) {
		return QJsonDocument();
	}
	QByteArray responsebody = reply->readAll();
	tDebug("response return %s", responsebody.constData());
	doc.fromJson(responsebody);
	reply->deleteLater();
	return doc;
}


QNetworkReply * Elastic::Send(const QNetworkRequest &requestbody,const QString&method, QByteArray & body)
{
	try {
		QEventLoop loop;
		QNetworkAccessManager network;	
		QBuffer buffer(&body);
		tDebug("Send request to server %s: method %s,url: %s, body:%s",requestbody.url().host().toStdString().c_str(),method.toStdString().c_str(), requestbody.url().toString().toStdString().c_str(),qPrintable(body));
		QNetworkReply * reply =network.sendCustomRequest(requestbody, method.toUtf8(), &buffer);
		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();
		tDebug("test %d", reply);

		tDebug("test")
		if (!reply) {
			tFatal("Request error! response NULL;");
		} else if (reply->error() != QNetworkReply::NoError&&(reply->error()<200|| reply->error() >= 400)) {
			tDebug("Request error! response code: %d, response messae: %s", reply->error(), qPrintable(reply->errorString()));
		}
		return reply;
	}
	catch (
		QException ex
		) {
		tFatal("In %s cause error %s", __FUNCTION__, ex.what());
		return nullptr;
	}
}
