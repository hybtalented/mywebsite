#include "jstoolscontroller.h"


void JstoolsController::base64transfer()
{
    // write code
	THttpResponse& response = httpResponse();
	switch (httpRequest().method()) {
	case Tf::Get:
		render();
		break;
	case Tf::Post:	
		auto obj = httpRequest().formItems("jstools");
		auto requesttype = obj["type"].toString();
		if (requesttype != "") {
			if (requesttype == "download") {
				auto base64 = obj["base64"].toString();
				auto filename = obj["filename"].toString();
				auto fileobj = QByteArray::fromBase64(base64.toLocal8Bit(), QByteArray::Base64Option::Base64Encoding);
				response.header().setContentType(u8"multipart/form-data");
				response.header().setRawHeader("Content-Disposition", QString(u8"attachment; filename=\"%1\"").arg(filename).toUtf8());
				response.setBody(fileobj);
			}
			else if (requesttype == "jsonformat") {
				auto doc = obj["jsontext"].toString();
				QJsonDocument jsondoc = QJsonDocument::fromJson(doc.toUtf8());
				response.header().setContentType(u8"application/text");
				response.setBody(jsondoc.toJson(QJsonDocument::Indented));
			}
			else if (requesttype == "jsoncompress") {
				auto doc = obj["jsontext"].toString();
				QJsonDocument jsondoc = QJsonDocument::fromJson(doc.toUtf8());
				response.header().setContentType(u8"application/text");
				response.setBody(jsondoc.toJson(QJsonDocument::Compact));
			}
		}
		break;
	}
}

// Don't remove below this line
T_DEFINE_CONTROLLER(JstoolsController)
