#ifndef BALL_H
#define BALL_H
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



#include"Coord.h"
#include"Point.h"
#include"mainwindow.h"
#include<QPair>




class Ball : public QObject, public QGraphicsItem, virtual public Point
{
    Q_OBJECT
public:

    enum class Type { PAINTED=1, STRIPPED,WHITE,BLACK };			//тип шаров:  сплошные, полосатые, белый и черный
    Ball();
    Ball(Coord coord=Coord(0,0) , int number=-1 , QColor color=Qt::yellow
            , Type type=Type::PAINTED, double scale=1, QGraphicsItem * parent=nullptr);
    Ball(const Ball& other);
    Ball& operator=(const Ball& other);
    ~Ball();
    static void setBallRadius(double scale); //устанавливает радиус всех шаров согласно сквозному масштабу
protected:

    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    QPainterPath shape() const;

protected:
    int number; //номер шара

    static double r;						//радиус

    QColor color;   //цвет
    Type type;      //тип шара: полосатый, сплошной , белый или черный
    bool active;		//шар на столе
    bool moving;        //шар в движении
    bool calculated;		//шар не просчитан за текущий цикл
    double scale;       //масштаб
    QFont * _font;      //шрифт шадписи

public:

    double distance(Ball& other);       //возвращает КВАДРАТ расстояние между шарами
    bool isTouch(V currV, V otherV, Coord &otherCoord);	//проверка на касание шаров. см аннотацию

    void collisionTwoBalls(Ball &other);				//обработка столкновения двух шаров
    void collisionThreeBalls(Ball &first, Ball& second);				//обработка столкновения трех шаров

    bool isMoving();
    bool isActive();
    bool isCalculated();
    bool isGameBall();      //возвращает истину, если шар полосаты или сплошной

    QColor getColor();
    Type getType();
    QPointF centerPos();        //для отладки
    void setActiveStatus(bool active);
    void setMovingStatus(bool moving);      //установка статууса движущегося шара вручную
    void setMovingStatus();
    void setCalculatedStatus(bool calc);
    void setSpeed(double, double);      //установка начальной скорости шара

    void setCoords(Coord const &coord);     //установка начальных координат шара
    void setCoords(double,double);

    void move();        //провижение шара на один цикл

friend class MainWindow;
friend class Table;
/////////!!!TEST!!!!///////////
public:
    void _moveTest();
    double _distanceTest(Ball& other);
    void posDifference();
};
#endif // BALL_H
