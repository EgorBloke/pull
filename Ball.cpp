#include"Ball.h"
#include<QDebug>
#include<QMouseEvent>


///////////////////////
double Ball:: r=49.;

////////////////////////
Ball::Ball()
{
    qDebug()<<"default constructor called";
    //this->setPos(150,150);
    /*_font = new QFont();
    _font->setBold(true);
    _font->setPixelSize(20);*/

}
Ball::Ball(Coord coord, int number, QColor color, Ball::Type type, double scale, QGraphicsItem * parent):QGraphicsItem(parent)
{
    qDebug()<<"main constructor called";
    /*_font = new QFont();
    _font->setBold(true);
    _font->setPixelSize(20);*/

    this->x0 = coord.x;		//устанавливаем координаты относительно первого шара
    this->y0 = coord.y;
    this->color = color;
    this->number = number;					//номер шара по порядку
    this->scale=scale;
    //this->setPos(x0,y0);



    this->type = type;

    this->active = true;							//шар на столе
    this->calculated = false;						//шар еще не просчитан (мб не нужно)

    //Balls.emplace_back(*this);						//кидаем шар в контейнер активных шаров
    //this->number = numbersArr[(int)color][(int)type]; //устанавливаем номер в зависимости от цвета и типа
    _font = new QFont();

}

Ball::~Ball()
{
   // delete _font;
    qDebug()<<"ball deleted";
}

void Ball::setBallRadius(double scale)
{
    Ball::r*=scale;
}



Ball::Ball(const Ball &other)
{
    qDebug()<<"copy constructor called";
    this->x0=other.x0;
    this->y0=other.y0;
    this->v0=other.v0;
    //this->v=other.v;
    this->color=other.color;
    this->type=other.type;
    this->number = other.number;
    this->active=other.active;
    this->moving=other.moving;
    this->calculated=other.calculated;

}

Ball &Ball::operator=(const Ball &other)
{
    qDebug()<<"operator = called";
    return *this;
}

QRectF Ball::boundingRect() const
{
    return QRectF(-r, -r, 2*r, 2*r);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double k=1.00;
//    painter->scale(scale,scale);
    painter->setBrush(QBrush(this->color,Qt::SolidPattern));
    painter->drawEllipse(QPointF(0,0),r*k,r*k);
    if(this->type==Type::PAINTED||this->type==Type::BLACK){
        painter->setBrush(QBrush(Qt::white,Qt::SolidPattern));
        painter->drawEllipse(QPointF(0,0),r*k*0.45,r*k*0.45);
    }
    if(this->type==Type::STRIPPED){
        painter->setBrush(QBrush(Qt::white,Qt::SolidPattern));
        painter->drawEllipse(QPointF(0,0),r*k*0.7,r*k*0.7);
    }

    _font->setBold(true);
    _font->setPixelSize(9);
    painter->setFont(*_font);
    painter->drawText(QRectF(-r, -r, 2*r, 2*r),Qt::AlignCenter,
                      tr("%1").arg(QString::number(number)));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//Ball & Ball::operator()(const Coord &coord)
//{
//    this->x0 = coord.x;		//устанавливаем координаты относительно первого шара
//    this->y0 = coord.y;
//    return *this;
//}

double Ball::distance(Ball &other)
{
    double tmp = (this->x() - other.x()) * (this->x() - other.x()) + (this->y() - other.y()) * (this->y() - other.y());
    return tmp;
}

//bool Ball::isTouch(V currV, V otherV)
//{

//    V tmp = currV-otherV;
//    if(abs(otherV.x)<0.001)
//    {
//        otherV.x=0;
//    }
//    if(abs(otherV.y)<0.001)
//    {
//        otherV.y=0;
//    }
////    V tmp = otherV-currV;
////    if(currV*otherV==0){
////        return false;
////    }
//    double result=tmp.x*currV.x+tmp.y*currV.y;
//    qDebug()<<tmp.x<<tmp.y;
//    return result>0;

//    //    return currV.vectorLenghtSquare()>otherV.vectorLenghtSquare();
//}

bool Ball::isTouch(V currV, V otherV, Coord &otherCoord)
{
    V otherCenterVector(otherCoord.x,otherCoord.y);
    V tmp = (currV-otherV);
    double result = tmp<<otherCenterVector; //скалярное произведение
    return result>=0;    //если скалярное произведение больше
        //или рано 0, то шары двигаются навстречу друг другу
}

double Ball::_distanceTest(Ball &other)
{

    double tmp = (this->x0 - other.x0) * (this->x0 - other.x0) + (this->y0 - other.y0) * (this->y0 - other.y0);
    return tmp;
}

void Ball::move()
{
    moveBy(this->v0.x * MainWindow::deltaT, this->v0.y * MainWindow::deltaT);

    V vPrev = this->v0;
    this->v0 *= MainWindow::deltaV;
    MainWindow::deltaV*=MainWindow::deltaForce;
    if ((fabs(vPrev.x - this->v0.x) < MainWindow::deltaVmin) &&
            (fabs(vPrev.y - this->v0.y) < MainWindow::deltaVmin))
    {
        this->setMovingStatus(false);
    }
}

void Ball::_moveTest()
{
    moveBy(this->v0.x * MainWindow::deltaT, this->v0.y * MainWindow::deltaT);

    V vPrev = this->v0;
    this->v0 *= MainWindow::deltaV;
    if ((fabs(vPrev.x - this->v0.x) < MainWindow::deltaVmin) && (fabs(vPrev.y - this->v0.y) < MainWindow::deltaVmin))
    {
        this->setMovingStatus(false);
    }
    //scene()->update();
}



void Ball::posDifference()
{
    qDebug()<<"ScenePos=" <<this->scenePos()<<";  "<<this->x()<<' '<<this->y();
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(0,0),r,r);
    return path;
}



bool Ball::isMoving()
{
    return moving&&this->isActive();
}

void Ball::collisionTwoBalls(Ball &other)
{
 //   qDebug()<<"this"<<this->x()<<this->y();
  //  qDebug()<<"other"<<other.x()<<other.y();
//
    Coord otherBallCoord(other.x() - this->x(), other.y() - this->y()); //координаты шара other относительно центр шара this
    if(abs(otherBallCoord.x)<0.001)
    {
        if(this->isTouch(this->v0.y, other.v0.y,otherBallCoord))
        {
            qSwap(this->v0.y,other.v0.y);
        }
    }
    else if(abs(otherBallCoord.y)<0.001)
    {

        if(this->isTouch(this->v0.x,other.v0.x,otherBallCoord))
        {
            qSwap(this->v0.x,other.v0.x);
        }
    }
    else{
        QPair<V,V> thisVProection=this->v0.makeProection(otherBallCoord);
        QPair<V,V> otherVProection=other.v0.makeProection(otherBallCoord);

        if (this->isTouch(thisVProection.first,otherVProection.first,otherBallCoord))
        {
            qSwap(thisVProection.first,otherVProection.first);
        }
        this->v0=this->v0.addTwoVector(thisVProection);
        other.v0=other.v0.addTwoVector(otherVProection);

    }
    this->setMovingStatus();
    other.setMovingStatus();
}

void Ball::collisionThreeBalls(Ball &first, Ball &second)
{
    Coord firstBallCoord(first.x() - this->x(), first.y() - this->y());     //координаты шара first относительно центр шара this
    Coord secondBallCoord(second.x() - this->x(), second.y() - this->y());      //координаты шара second относительно центр шара this

    V thisVProectionOnFirst = this->v0.makeRhombProection(firstBallCoord, secondBallCoord);      //делаем проекцию скорости шара зис на прямую до центра первого шара
    QPair<V,V> firstVProection = first.v0.makeProection(firstBallCoord);        //проекция скорости первого шара на пряму между центрами с ЗИС



    V thisVProectionOnSecond = this->v0.makeRhombProection(secondBallCoord, firstBallCoord );    //тоже самое со вторым шаром
    QPair<V,V> secondVProection= second.v0.makeProection(secondBallCoord);

    qSwap(firstVProection.first,thisVProectionOnFirst);     //меняем скорости местами
    qSwap(secondVProection.first,thisVProectionOnSecond);

    this->v0=this->v0.addTwoVector(qMakePair(thisVProectionOnFirst,thisVProectionOnSecond));  //собираем вектора скорости для всех шаров
    first.v0=first.v0.addTwoVector(firstVProection);
    second.v0=second.v0.addTwoVector(secondVProection);

    this->setMovingStatus();  //проверка на движения шаров
    first.setMovingStatus();
    second.setMovingStatus();
}

bool Ball::isActive()
{
    return active;
}

bool Ball::isCalculated()
{
    return this->calculated&&this->isActive();
}

bool Ball::isGameBall()
{
    return this->getType()== Type::PAINTED||this->getType()==Type::STRIPPED;
}

Ball::Type Ball::getType()
{
    return this->type;
}

QPointF Ball::centerPos()
{
    return this->pos()+QPointF(r,r);
}

void Ball::setActiveStatus(bool active)
{
    this->active=active;
}

void Ball::setMovingStatus(bool moving)
{
    this->moving=moving;
}

void Ball::setMovingStatus()
{
    this->moving = !this->v0.isNull();
}

void Ball::setCalculatedStatus(bool calc)
{
    this->calculated=calc;
}

void Ball::setSpeed(double Vx, double Vy)
{
    this->v0.x=Vx;
    this->v0.y=Vy;
}





void Ball::setCoords(Coord const &coord)
{
    this->x0=coord.x;
    this->y0=coord.y;

}

void Ball::setCoords(double x, double y)
{
    this->x0=x;
    this->y0=y;
}
