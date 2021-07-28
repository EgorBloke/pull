#include"Point.h"
#include<cmath>

Point::Point(Coord coord)
{
    this->x0 = coord.x;
    this->y0 = coord.y;
}



void Point::moving(double deltaT)
{

}

double Point::distance(Point& other) {
    double tmp = (this->x0 - other.x0) * (this->x0 - other.x0) + (this->y0 - other.y0) * (this->y0 - other.y0);
    return tmp;
}

void Point::setV(double Vx, double Vy)
{
    this->v0.x=Vx;
    this->v0.y=Vy;
}

void Point::setV(V v)
{
    this->v0.x=v.x;
    this->v0.y=v.y;

}
