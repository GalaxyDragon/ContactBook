#ifndef USERINFOWIDGET_H
#define USERINFOWIDGET_H
#include "userinfo.h"
#include "utility.h"


#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QFileDialog>
#include <QFile>
#include<QObject>
class InfoWidget: public QWidget
{
    Q_OBJECT
    /*
     * Виджет вида
     *  заголовок:
     *         ДАННЫЕ
     */
public:
    InfoWidget(QString hl, QString data, QWidget *parent = nullptr);

signals:

public slots:
private:
    QGridLayout* _thisLayout;
    QLabel _headline;
    QLabel _data;

};

class EditWidget_LineEdit: public QWidget
{
    Q_OBJECT
    /*
     * Виджет вида
     *  заголовок:
     *         ПОЛЕ ДЛЯ ВВОДА(T)
     */
public:
    explicit EditWidget_LineEdit(QString h, QWidget *parent = nullptr)
        :QWidget (parent)
    {
        _thisLayout = new QGridLayout;
        _defaultHeadline = h;
        _headline.setText(h);
        _data = new QLineEdit();
        _thisLayout->addWidget(&_headline,0,0);
        _thisLayout->addWidget(_data,1,1);
        setLayout(_thisLayout);
        QObject::connect(_data,SIGNAL(textChanged(const QString)),this,SLOT(SetDefaultHeadline()));
    }
    QString GetData(){
        return _data->text();
    }
    void Clear(){
        _data->clear();
    }
    void SetTemperanseHeadline(QString temp){
        _headline.setText(temp);
    }


signals:

public slots:
    void SetDefaultHeadline(){
        _headline.setText(_defaultHeadline);
    }
private:
    QGridLayout* _thisLayout;
    QLabel _headline;
    QLineEdit* _data;
    QString _defaultHeadline;

};

//Основной виджет, показывающий всю информацию о пользователе
class UserInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserInfoWidget(UserInfo* data,QWidget *parent = nullptr);

signals:

public slots:

private:
    QGridLayout* _thisLayout;
    QLabel* photoLabel;
};

//виджет создания пользователя
class UserInfoWidgetCreator : public QWidget
{
    Q_OBJECT
public:
    explicit UserInfoWidgetCreator(QWidget *parent = nullptr);
    //очистка полей при удачном создании пользователя
    void FlushFields();

signals:
    void SendUser(UserInfo* newUser);
public slots:
    //соединён с кнопкой. Проверяет, что нужные поля заполненны
    // и вызывает сигнал SendUser
    void CreateUser();
    void UpdatePhoto();
    
private:
    QGridLayout* _thisLayout;
    ClickableLabel* _avatar;
    QString _imagePath = ":/image/testo.jpg";
    EditWidget_LineEdit* _firstName;
    EditWidget_LineEdit* _secondName;
    EditWidget_LineEdit* _thirdName;
    long long int ID = UsersId::getId();
    QPushButton* _okButton;
};

#endif // USERINFOWIDGET_H
