#ifndef INFORMATIONMAILER_H
#define INFORMATIONMAILER_H

#include <TActionMailer>


class InformationMailer : public TActionMailer
{
public:
    InformationMailer() { }
    void send(const QString& to,const QString & body, const QString&from = "hybtalented@163.com");
};

#endif // INFORMATIONMAILER_H
