#ifndef MYSCENE_H
#define MYSCENE_H
#include <QMainWindow>
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QVector>
#include <QGraphicsView>
#include<QTimer>
 class MyScene : public QGraphicsScene{
     MyScene(QGraphicsScene * parent);


     // QGraphicsScene interface
 protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
 };

#endif // MYSCENE_H
