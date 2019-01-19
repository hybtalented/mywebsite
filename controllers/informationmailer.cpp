#include "informationmailer.h"


void InformationMailer::send(const QString& to,const  QString & body, const QString&from)
{
    //
    // write code
    //
	texport(to);
	texport(body);
	texport(from);
	tInfo("Sending the from %s to %s with the message (%s)", from.toUtf8().constData(),to.toUtf8().constData(), body.toUtf8().constData());
    deliver("mail");
}


