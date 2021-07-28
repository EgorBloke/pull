#include"Table.h"
#include"Ball.h"
#include"mainwindow.h"

const double Table::defaultTableHeight{2660};
const double Table::defaultClothWidht{1270};
const double Table::defaultClothHeight{2540};
const double  Table::defaultBallRadius = Ball::r;
const double Table:: defaultBoardSize= 120;
extern MainWindow * w;
Table::Table(double maxHeight,QObject *parent) : QObject(parent)
{

    scale = maxHeight/defaultTableHeight;

    ballRadius = defaultBallRadius*scale;
    tableHeight=defaultTableHeight*scale;
    clothWidht=defaultClothWidht*scale;
    clothHeight=defaultClothHeight*scale;
    boardSize = defaultBoardSize*scale;
    double d = ballRadius*2;
    vecInside<<QPointF(d,0)
            <<QPointF(clothWidht-d,0)
            <<QPointF(clothWidht,d)
            <<QPointF(clothWidht,clothHeight-d)
            <<QPointF(clothWidht-d,clothHeight)
            <<QPointF(d,clothHeight)
            <<QPointF(0,clothHeight-d)
            <<QPointF(0,d)
            <<QPointF(d,0);
    vecOutside<<QPointF(-boardSize,-boardSize)
             <<QPointF(clothWidht+boardSize,-boardSize)
             <<QPointF(clothWidht+boardSize,clothHeight+boardSize)
            <<QPointF(-boardSize,clothHeight+boardSize)
           <<QPointF(-boardSize,-boardSize);
    QPolygonF insidePolyg(vecInside);
    QPolygonF ousidePolyg(vecOutside);

    insideColor = QColor(QRgb(0x0A4500));
    outsideColor = QColor(QRgb(0x714B23));
}

double Table::getScale()
{
    return this->scale;
}

double Table::getClothWidht()
{
    return clothWidht;
}

double Table::getClothHeight()
{
    return clothHeight;
}

QPointF Table::getWhiteBallWaitingPos()
{
    return whiteBallWaitingPos;
}

QPointF Table::getBlackBallWaitingPos()
{
    return blackBallWaitingPos;
}



QRectF Table::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void Table::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->scale(scale,scale);
    QPainterPath outsidePath;
    outsidePath.addPolygon(vecOutside);

//    painter->fillPath(outsidePath,outsideColor);
    QBrush br(QColor(QColor(QRgb(0x331a00))),Qt::SolidPattern);
  //  QBrush(QImage(":/img/tableBoard.PNG"))
    painter->fillPath(outsidePath,br);
    painter->drawPath(outsidePath);

    QPainterPath insidePath;
    insidePath.addPolygon(vecInside);
    painter->fillPath(insidePath,insideColor);
    painter->drawPath(insidePath);
//    QString ballType="no type";
//    QString name = tr("%1").arg(w->getActivePlayer().getName());
//    if(w->getActivePlayer().getBallType()==Player::BallType::PAINTED){
//        ballType="Painted";
//    }
//    else if(w->getActivePlayer().getBallType()==Player::BallType::STRIPPED){
//        ballType="Stripped";
//    }

//    painter->setPen(QColorConstants::Svg::black);
//    painter->drawText(QRectF(0, -50, 225, 25),Qt::AlignCenter, name+" move; "+ballType+" balls");
    ////DRAWPOCKET

//    pocket->paint(painter,option,widget);

//    QPainterPath pathPocket;
//    pathPocket.addPolygon(pocket->vec);

//    painter->fillPath(pathPocket,Qt::black);
//    painter->drawPath(pathPocket);



//    painter->setBrush(QBrush(insideColor,Qt::SolidPattern));
//    painter->drawPolygon(vecInside);
//    painter->fillPath(vecInside,QBrush(insideColor,Qt::SolidPattern));
    //    painter->setBackground(QBrush(insideColor,Qt::SolidPattern));
}


