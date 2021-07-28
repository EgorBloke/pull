#ifndef POCKET_H
#define POCKET_H

#include<QGraphicsRectItem>
#include<QObject>  //!!!!
#include<QPaintEvent>
#include<QPainter>
#include<QWidget>
#include<QGraphicsItem>
#include<QStyleOptionGraphicsItem>
#include<QFont>
#include<QPoint>
#include<QDebug>
#include<QTimer>
#include<QMainWindow>

class Pocket:public QObject, public QGraphicsItem
{
Q_OBJECT
public:
    Pocket(QPointF pocketPoint=QPointF(0,0), double alpha=0, double ballRadius=57., double delta=1.44, QGraphicsItem *parent = nullptr);
protected:
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
protected:
    //////VARIABLES///////
    double deltaPocket;
    double alpha;
    double ballRadius;
    QPolygonF rect;
    QPointF pocketPoint;
    QVector<QPointF> vec;
};

#endif // POCKET_H
