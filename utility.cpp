#include "utility.h"
VerticalScrollArea::VerticalScrollArea(QWidget* content, QWidget *parent)
    : QScrollArea(parent)
{
    setWidgetResizable(true);
    setFrameStyle(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QWidget* m_scrollAreaWidgetContents = content;
    m_scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setWidget(m_scrollAreaWidgetContents);
}

ClickableLabel::ClickableLabel(QWidget* parent):QLabel(parent){}
void ClickableLabel::mousePressEvent(QMouseEvent* event){
    emit Clicked();
}

long long int UsersId::id=0;
