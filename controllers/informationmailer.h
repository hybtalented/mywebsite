#ifndef INFORMATIONMAILER_H
#define INFORMATIONMAILER_H

#include <TActionMailer>
#include <tappsettings.h>
class InformationMailer : public TActionMailer
{
public:
    InformationMailer() { }
    void send(const QString& to,const QString & body, const QString& subject ,const QString&from = TAppSettings::instance()->readValue("ActionMailer.smtp.UserName","hybtalented@163.com").toString());
};

#endif // INFORMATIONMAILER_H
