#include"mygraphicsview.h"
#include<QDebug>
#include "mainwindow.h"

extern MainWindow * w;
MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<"MyGraphicsView::mousePressEvent";
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
//    qDebug()<<"MyGraphicsView::mouseReleaseEvent";
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
//        qDebug()<<"MyGraphicsView::mouseMoveEvent";
    if(w->isGameActive()){
        w->setCueRotation((mapToScene(event->pos())-QPointF(w->TABLE_OFFSET_X,w->TABLE_OFFSET_X)));  ///FIXIT!!!!!!!!!
    }

//    w->setCueRotation((event->pos()-QPointF(70,70)));  ///FIXIT!!!!!!!!!

    QGraphicsView::mousePressEvent(event);

}

