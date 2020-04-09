#include "mainwindow.h"
#include <QApplication>
#include "userinfowidget.h"//правое окно, в котором содержится инфо
#include "userlistwidget.h"//левый список людей
#include "usersmainwidget.h"//главный виджет, объединяющий всё
#include "testo.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QVector<UserInfo*> tst;
    tst.push_back(TESTO::DummyUser());
    for(int i=0; i<0;++i){
        tst.push_back(new UserInfo("Хоп","Хей","Ла-ла-лей"));//TESTO::DummyUser());
        tst.last()->imagePath=":/image/testo.jpg";
    }
    QSettings settings( "settings.conf", QSettings::IniFormat );
        settings.beginGroup("GlobalPaths");
        settings.setValue("PhotoPath","D:\\Projects\\ph\\");
        settings.endGroup();
    UsersMainWidget w(tst);

    w.show();

    return a.exec();
}
