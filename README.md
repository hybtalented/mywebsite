# mywebsite
my personal website use treefrog framework

# project request externel libararies
1. [treefrog framework version 1.22.0](http://www.treefrogframework.org)
2. [freetype version 2.4.0 ](https://www.freetype.org)
2. [poppler version 0.73.0](https://poppler.freedesktop.org)

# install steps
* install by hand
    1. install QT5
    2. install treefrog
    3. install sendmail package
    4. edit the /etc/mail/sendmail.mc
        set the line to allow the no localhost access to sendmail
            DAEMON_OPTIONS(`Family=inet,  Name=MTA-v4, Port=smtp, Addr=0.0.0.0')
        then update the configuration
            m4 /etc/mail/sendmail.mc > /etc/mail/sendmail.cf