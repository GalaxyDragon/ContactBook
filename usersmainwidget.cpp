#include "usersmainwidget.h"

UsersMainWidget::UsersMainWidget(QVector<UserInfo*>& data, QWidget *parent) : QWidget(parent)
{
    addUserButton = new QPushButton("Add");
    searchTab = new QLineEdit;
    this->data = &data;
    listOfUsers = new UserListWidget(&data,this);
    for(auto x:listOfUsers->totalCells){
        QObject::connect(x,SIGNAL(Clicked(UserInfo*)),this,SLOT(UpdateUser(UserInfo*)));
        //апдейт отображающегося юзера при клике

    }
    if(data.empty()){
        infoWindow = new UserInfoWidget(TESTO::DummyUser());
    }else{
        infoWindow = new UserInfoWidget(data[0]);
    }
    QGridLayout* topSearchBar = new QGridLayout;
    topSearchBar->addWidget(searchTab,0,0,1,3);
    topSearchBar->addWidget(addUserButton,0,3);
    //mainLayout.addWidget(addUserButton,0,0);
    //mainLayout.addWidget(searchTab,1,0);
    mainLayout.addLayout(topSearchBar,0,0);
    mainLayout.addWidget(new VerticalScrollArea(listOfUsers),1,0);
    mainLayout.addWidget(infoWindow,1,1);
    setLayout(&mainLayout);
    //соединение различных слотов и сигналов
    QObject::connect(addUserButton,SIGNAL(released()),this,SLOT(UpdateToCreateWindow()));
    QObject::connect(searchTab,SIGNAL(textEdited(const QString&)),this,SLOT(SearchUsers(QString)));
}
//Вывести на окно данные нового юзера
void UsersMainWidget::UpdateUser(UserInfo* data){
    UserInfoWidget* tempInfoWidget = new UserInfoWidget(data);
    auto* currentWidget = mainLayout.itemAtPosition(1,1)->widget();
    mainLayout.replaceWidget(currentWidget,tempInfoWidget,Qt::FindChildrenRecursively);
    //небольшо костыль, чтобы layout удалился после выхода из функции
    QWidget().setLayout(currentWidget->layout());
    infoWindow = tempInfoWidget;
}
//вывести окно создания пользователя
void UsersMainWidget::UpdateToCreateWindow(){
    auto* currentWidget = mainLayout.itemAtPosition(1,1)->widget();
    UserInfoWidgetCreator* tempWidget = new UserInfoWidgetCreator;
    mainLayout.replaceWidget(currentWidget,tempWidget,Qt::FindChildrenRecursively);
    QWidget().setLayout(currentWidget->layout());
    QObject::connect(tempWidget,SIGNAL(SendUser(UserInfo*)),this,SLOT(AddUser(UserInfo*)));

}
//добавить переданного пользователя
void UsersMainWidget::AddUser(UserInfo* data){
    this->data->push_back(data);
    listOfUsers->totalCells.push_back(new ListCell(data));
    listOfUsers->mainLayout.addWidget(listOfUsers->totalCells.last(),listOfUsers->totalCells.size()-1);
    mainLayout.update();
    QObject::connect(listOfUsers->totalCells.last(),SIGNAL(Clicked(UserInfo*)),this,SLOT(UpdateUser(UserInfo*)));
}
void UsersMainWidget::SearchUsers(QString data){
    listOfUsers->SearchUsers(data);
    for(ListCell* x:listOfUsers->totalCells){
        QObject::connect(x,SIGNAL(Clicked(UserInfo*)),this,SLOT(UpdateUser(UserInfo*)));
        //апдейт отображающегося юзера при клике
    }
}
