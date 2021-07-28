#ifndef V_H
#define V_H
#include<QPair>
#include"Coord.h"

class V			//тип данных для скорости
{
public:
    V(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
    }
    double x, y;
    V operator-(const V& other);
    V operator+(const V& other);
    V operator*(double a);
    double operator<<(const V& other);      //скалярное произведение
    V& operator*=(double value);
    bool operator<(const V& other);
    double value();			//возвращает значение скорости по модулю
    bool operator==(const V& other);

     QPair<V,V> makeProection(double pointX, double pointY);
     QPair<V,V> makeProection(Coord coord);


     V makeRhombProection(Coord firstCoord, Coord secondCoord);


     V addTwoVector (QPair<V,V> pair);
     double vectorLenghtSquare();
    bool isNull();

     friend class Ball;
};

#endif // V_H
