#ifndef USERLISTWIDGET_H
#define USERLISTWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "userinfo.h"
#include "testo.h"

class ListCell: public QWidget
{
    Q_OBJECT
public:
    void  mousePressEvent ( QMouseEvent * event );
    explicit ListCell(UserInfo* target, QWidget *parent = nullptr);
signals:
    void Clicked(UserInfo* data);
public slots:
private:
    UserInfo* _userAbout;
    QLabel* nameLabel;
    QGridLayout mainLayout;
};


class UserListWidget : public QWidget
{
    Q_OBJECT
public:
    QVector<ListCell*> totalCells;//вектор, в котором хранятся ячейки итогового списка
    QVBoxLayout mainLayout;
    explicit UserListWidget(QVector<UserInfo*>* dataList, QWidget *parent = nullptr);
    void SearchUsers(QString& filter);
signals:

public slots:

private:
    QVector<UserInfo*>* data;
};

#endif // USERLISTWIDGET_H
