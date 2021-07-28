#include"Cue.h"


double Cue::maxPower = 5000;
extern MainWindow * w;
Cue::Cue(QGraphicsItem* parent):QGraphicsItem(parent)
{

    vector<<QPointF(35,0)<<QPointF(250,-1.5)<<QPointF(250,1.5);
    cueTimer = new QTimer();
    connect(cueTimer,SIGNAL(timeout()),this,SLOT(gainPower()));
}

void Cue::setCuePower(double power)
{
    this->power=power;
}

double Cue::getPower()
{
    return power;
}

double Cue::getMaxPower()
{
    return maxPower;
}

QRectF Cue::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void Cue::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setBrush(QBrush(this->color,Qt::SolidPattern));
    painter->drawPolygon(vector);

    QPen pen(Qt::white);
    pen.setStyle(Qt::DashLine);
    pen.setDashOffset(15);
    painter->setPen(pen);
    painter->drawLine(0,0,-350,0);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Cue::gainPower()
{
    power+=(power<=maxPower)? deltaPower:0;
}








