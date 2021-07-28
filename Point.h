#ifndef POINT_H
#define POINT_H
#include"Coord.h"
#include"V.h"




class Point {

public:
    Point() :x0(0), y0(0), v0(0, 0) {}
    Point(Coord coord);
protected:
    double t = 0.02;		 //приращение времени
    double x0, y0;			//начальные координаты
    V v0;		//начальная скорость
public:
    void moving(double deltaT);		//приращение координат
    virtual double distance(Point& other);	//измерение дистанции между шарами
    void setV(double Vx, double Vy);							//устанавливает начальную скорость
    void setV(V v);							//устанавливает начальную скорость
    void setAlpha(double alpha);			//устанавливает угол

    friend class MainWindow;
};


#endif // POINT_H
