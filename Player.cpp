#include"Player.h"
extern MainWindow * w;
Player::Player(QString name, double ballRadius,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->ballRadius=ballRadius;
    this->name=name;
    firstBallPos=QPointF(ballRadius+1,65-ballRadius-1);
    for(int i=0;i<8;++i){
        ballsPos<<firstBallPos+QPointF(ballRadius*2*i,0);
    }
    _font = new QFont();

}

bool Player::isLastBall()
{
    return ballCount >= 7;

}

bool Player::isActive()
{
    return active;

}

bool Player::isPreparingKick()
{return preparingKick;

}

void Player::addBallToShelf()
{

}

void Player::setBallType(BallType ballType)
{
    this->ballType=ballType;
}

void Player::setPreparingKickStatus(bool status)
{
    preparingKick=status;
}

QString Player::getName()
{
    return name;
}

int Player::getBallCount()
{
    return ballCount;
}

void Player::raiseBallCount(int balls)
{
    ballCount+=balls;
}

QPointF Player::getNextBallShelfPoint()
{
    return ballsPos[ballCount-1];
}

void Player::setActiveStatus(bool status)
{
    this->active=status;
}

QRectF Player::boundingRect() const
{
    return QRect(0,0,150,50);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColorConstants::Svg::black);
    painter->drawRect(0,0,195,25);
    _font->setBold(true);
    _font->setPixelSize(15);
    painter->setFont(*_font);
    if(isActive())
    {
        if (preparingKick){
            painter->setBrush(QBrush(QColorConstants::Svg::green,Qt::SolidPattern));
            painter->drawRect(0,0,195 * w->cue->getPower()/Cue::getMaxPower(),25);
        }
        else{
            painter->setBrush(QBrush(QColorConstants::Svg::green,Qt::SolidPattern));
            painter->drawRect(0,0,195 ,25);
        }

    }
    else {
        painter->setBrush(QBrush(QColorConstants::Svg::brown,Qt::SolidPattern));
        painter->drawRect(0,0,195,25);
    }

//    painter->drawText(QRectF(-r, -r, 2*r, 2*r),Qt::AlignCenter,tr("%1").arg(QString::number(number)));

    if(ballType==BallType::NO_TYPE){

        painter->setBrush(QBrush(Qt::white,Qt::SolidPattern));
        painter->drawEllipse(QPointF(195-2*ballRadius,-2*ballRadius*1.1),2*ballRadius,2*ballRadius);
        painter->drawText(QRectF(QPointF(195-4*ballRadius,-4*ballRadius),QPointF(195-2*ballRadius,-2*ballRadius)+QPointF(2*ballRadius,2*ballRadius)),
                          Qt::AlignCenter,"No");
    }
    else if (ballType==BallType::PAINTED){
        painter->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        painter->drawEllipse(QPointF(195-2*ballRadius,-2*ballRadius),2*ballRadius,2*ballRadius);
        painter->setBrush(QBrush(Qt::white,Qt::SolidPattern));
        painter->drawEllipse(QPointF(195-2*ballRadius,-2*ballRadius),2*ballRadius*0.37,2*ballRadius*0.37);
        painter->drawText(QRectF(QPointF(195-4*ballRadius,-4*ballRadius),QPointF(195-2*ballRadius,-2*ballRadius)+QPointF(2*ballRadius,2*ballRadius)),
                          Qt::AlignCenter,"P");

    }else if(ballType==BallType::STRIPPED){
        painter->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        painter->drawEllipse(QPointF(195-2*ballRadius,-2*ballRadius),2*ballRadius,2*ballRadius);
        painter->setBrush(QBrush(Qt::white,Qt::SolidPattern));
        painter->drawEllipse(QPointF(195-2*ballRadius,-2*ballRadius),2*ballRadius*0.60,2*ballRadius*0.60);
        painter->drawText(QRectF(QPointF(195-4*ballRadius,-4*ballRadius),QPointF(195-2*ballRadius,-2*ballRadius)+QPointF(2*ballRadius,2*ballRadius)),
                          Qt::AlignCenter,"S");;
    }

    painter->setBrush(QBrush(QColorConstants::Svg::black,Qt::SolidPattern));
    painter->setPen(QColorConstants::Svg::black);


    painter->drawText(QRectF(0, 0, 195, 25),Qt::AlignCenter, name);
//    painter->drawLine(0,65,195,65);
//    for(int i=0;i<8;++i){
//            painter->drawEllipse(ballsPos[i],ballRadius,ballRadius);
//    }

    scene()->update();

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

#include"Player.h"
