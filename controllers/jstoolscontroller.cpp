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
		if (httpRequest().hasJson()) {
			auto obj = httpRequest().jsonData();
			auto requesttype = obj["type"].toString();
			if (requesttype != "") {
				if (requesttype == "download") {
					auto base64 = obj["base64"].toString();
					qDebug() << base64;
					auto filename = obj["filename"].toString();
					auto fileobj = QByteArray::fromBase64(base64.toLocal8Bit(), QByteArray::Base64Option::Base64Encoding);
					response.header().setContentType("multipart/form-data");
					response.header().setRawHeader("Content-Disposition", filename.toUtf8());
					response.setBody(fileobj);
				}
			}
		}
		break;
	}
}

// Don't remove below this line
T_DEFINE_CONTROLLER(JstoolsController)
