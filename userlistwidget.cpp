#include "userlistwidget.h"

ListCell::ListCell(UserInfo* target, QWidget *parent)
    :_userAbout(target)
{
    QString _shortname = target->firstname;
    nameLabel = new QLabel();
    nameLabel->setText(_shortname);
    mainLayout.addWidget(nameLabel);
    setLayout(&mainLayout);
}

void ListCell::mousePressEvent(QMouseEvent* event){
    emit Clicked(_userAbout);
}


UserListWidget::UserListWidget(QVector<UserInfo*>* dataList,QWidget *parent) : QWidget(parent)
{
    data = dataList;
    int counter=0;
    for(UserInfo* unit:*dataList){
        totalCells.push_back(new ListCell(unit));
        mainLayout.addWidget(totalCells.last(),counter);
        ++counter;
    }
    setLayout(&mainLayout);
}

void UserListWidget::SearchUsers(QString& filter){
    QStringList items = filter.split(" ");
    QVector<UserInfo*> confirmed;  //список пользователей подошедших под условия
    for(UserInfo* user:*data){
        bool conf = true;
    for(QString& i:items){
        bool temp_conf = false;
        temp_conf = temp_conf || user->firstname.contains(i);
        temp_conf = temp_conf || user->secondname.contains(i);
        temp_conf = temp_conf || user->thirdname.contains(i);
        conf = conf && temp_conf;
    }

    if(conf){
        confirmed.push_back(user);
    }

    }
    totalCells.clear();
    for(int i=mainLayout.count()-1; i>=0;--i){
      auto x = mainLayout.takeAt(i)->widget();
      delete mainLayout.takeAt(i);
      x->deleteLater(); 
    }
    //пишем новые
    int counter=0;
    for(UserInfo* unit:confirmed){
        totalCells.push_back(new ListCell(unit));
        mainLayout.addWidget(totalCells.last(),counter);
        ++counter;
    }
    mainLayout.update();
}
