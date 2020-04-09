#include "userinfowidget.h"
InfoWidget::InfoWidget(QString hl, QString data, QWidget *parent)
{
    _thisLayout = new QGridLayout;
    _thisLayout->setSizeConstraint(QLayout::SetFixedSize);
    _headline.setText(hl);
    _data.setText(data);
    _thisLayout->addWidget(&_headline,0,0);
    _thisLayout->addWidget(&_data,1,1);
    setLayout(_thisLayout);
}

UserInfoWidget::UserInfoWidget(UserInfo* data,QWidget *parent):QWidget(parent){
    _thisLayout = new QGridLayout;
    static const QSize resultSize(1080, 1920);
    //аватарка
    QImage photo =  QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    photo.load(data->imagePath);
    photo = photo.scaled(300, 300,Qt::KeepAspectRatio);
    _thisLayout->setSizeConstraint(QLayout::SetFixedSize);
    photoLabel =new QLabel;
    photoLabel->setPixmap(QPixmap::fromImage(photo));
    //фамилия/имя
    InfoWidget* name = new InfoWidget("Имя",data->firstname);
    InfoWidget* surname = new InfoWidget("Фамилия",data->secondname);
    //компановка
    _thisLayout->addWidget(photoLabel,0,1,0,3);
    _thisLayout->addWidget(name,1,0);
    _thisLayout->addWidget(surname,2,0);

    setLayout(_thisLayout);

}

UserInfoWidgetCreator::UserInfoWidgetCreator(QWidget *parent)
    :_thisLayout(new QGridLayout),_avatar(new ClickableLabel)
{
    //создание полей интерфейса
    _avatar->setPixmap(QPixmap(":/image/testo.jpg").scaled(QSize(300,300),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    _firstName = new EditWidget_LineEdit("Имя");
    _secondName = new EditWidget_LineEdit("Фамилия");
    _thirdName = new EditWidget_LineEdit("Отчество");
    _okButton = new QPushButton("Создать");
    //компановка Layout
    _thisLayout->addWidget(_firstName,0,0);
    _thisLayout->addWidget(_secondName,1,0);
    _thisLayout->addWidget(_thirdName,2,0);
    _thisLayout->addWidget(_okButton,3,1);
    _thisLayout->addWidget(_avatar,0,1,3,3);
    //соединение слотов и виджетов
    QObject::connect(_okButton,SIGNAL(released()),this,SLOT(CreateUser()));
    QObject::connect(_avatar,SIGNAL(Clicked()),this,SLOT(UpdatePhoto()));
    setLayout(_thisLayout);
}
void UserInfoWidgetCreator::CreateUser(){
    //проверка условий
    if(_firstName->GetData()!="" && _secondName->GetData()!=""){
        UserInfo* result = new UserInfo(_firstName->GetData(),
                                        _secondName->GetData(),
                                        _thirdName->GetData());
        result->imagePath = _imagePath;
        //очистка
        FlushFields();

        emit(SendUser(result));
    }else{
        //вывод предупреждений
        if(_firstName->GetData()==""){
            _firstName->SetTemperanseHeadline("Имя:(обязательно)");
        }
        if(_secondName->GetData()==""){
            _secondName->SetTemperanseHeadline("Фамилия:(обязательно)");
        }
    }
}
void UserInfoWidgetCreator::UpdatePhoto(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp)"));
    QSettings settings("settings.conf",QSettings::IniFormat);
    //если при выборе файла что-то пошло не так
    if(fileName==""){
        return;
    }
    settings.beginGroup("GlobalPaths");
    QString targetPath = settings.value("PhotoPath").toString();
    if(!QDir(targetPath+QString::number(ID)).exists()){
        QDir(targetPath).mkdir(QString::number(ID));
    }
    targetPath+=QString::number(ID)+"\\";
    targetPath+=QString("avatar");
    QFile tempFile(targetPath);
    if(tempFile.exists()){
        tempFile.remove();
    }
    QFile::copy(fileName,targetPath);
    _avatar->setPixmap(QPixmap(targetPath).scaled(QSize(300,300),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    _imagePath = targetPath;

}

void UserInfoWidgetCreator::FlushFields(){
    _firstName->Clear();
    _secondName->Clear();
    _thirdName->Clear();
    _imagePath=":/image/testo.jpg";
    ID = UsersId::getId();
    _avatar->setPixmap(QPixmap(":/image/testo.jpg").scaled(QSize(300,300),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

}
