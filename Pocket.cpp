#include"Pocket.h"
Pocket::Pocket(QPointF pocketPoint, double alpha, double ballRadius, double delta, QGraphicsItem *parent)
{
    this->alpha=alpha;
    this->pocketPoint=pocketPoint;
    this->deltaPocket=delta;
    this->ballRadius=ballRadius;
    vec<<pocketPoint
       <<pocketPoint+QPointF(0, -ballRadius)
       <<pocketPoint+QPointF(2* ballRadius*deltaPocket,-ballRadius)
       <<pocketPoint+QPointF(2* ballRadius*deltaPocket,0)
        <<pocketPoint;
}

QRectF Pocket::boundingRect() const
{
//    return QRectF(pocketPoint.x(),pocketPoint.y(), 0, 0);
    return QRectF(0,0, 10, 10);
}


void Pocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath pathPocket;

    pathPocket.addPolygon(vec);
    painter->fillPath(pathPocket,Qt::black);
    painter->drawPath(pathPocket);
    painter->setBrush(QBrush(Qt::black));
    painter->drawChord(QRectF(pocketPoint-QPointF(0,2*ballRadius),QPointF(2* ballRadius*deltaPocket,2* ballRadius*deltaPocket)-QPointF(0,2*ballRadius)),0, 16*180);
}
