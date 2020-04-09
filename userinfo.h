#ifndef USERINFO_H
#define USERINFO_H
#include <QtWidgets>

class UserInfo
{
public:
    UserInfo(QString n1="",QString n2="",QString n3="");
    QString firstname;
    QString secondname;
    QString thirdname;
    QString imagePath=":/image/testo.jpg";
};

#endif // USERINFO_H
