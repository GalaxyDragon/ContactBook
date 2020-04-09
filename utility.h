#ifndef UTILITY_H
#define UTILITY_H
#pragma once
#include <QScrollArea>
#include <QLabel>

class VerticalScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit VerticalScrollArea(QWidget* content, QWidget *parent = nullptr);

signals:

public slots:
};


class ClickableLabel:public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr);

signals:
    void Clicked();
public slots:
private:
    void mousePressEvent(QMouseEvent* event);
};

class UsersId{
public:
    UsersId operator=(const UsersId& other) = delete;
    UsersId(const UsersId& other) = delete;
    static long long int getId(){return id++;}
    private:
    static long long int id;

};

#endif // UTILITY_H
