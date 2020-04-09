#ifndef USERSVIEWWIDGET_H
#define USERSVIEWWIDGET_H
#include "userinfo.h"
#include "userlistwidget.h"
#include "userinfowidget.h"
#include "testo.h"
#include "utility.h"
#include <QWidget>

class UsersMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UsersMainWidget(QVector<UserInfo*>& data, QWidget *parent = nullptr);
    UserListWidget* listOfUsers;
signals:

public slots:
    //сменить окно информаии на другого юзера
    void UpdateUser(UserInfo* data);
    //сменяет окно информации на оено создания
    void UpdateToCreateWindow();
    //слот, добавляющий юзера в список
    void AddUser(UserInfo* data);
    //обновляет список пользователей по информации поиска
    void SearchUsers(QString data);

private:
    QGridLayout mainLayout;
    QVector<UserInfo*>* data;
    UserInfoWidget* infoWindow;
    QPushButton* addUserButton;
    QLineEdit* searchTab;
};

#endif // USERSVIEWWIDGET_H
