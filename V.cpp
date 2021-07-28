#include"V.h"
#include"mainwindow.h"

V V::operator-(const V &other)
{
    V tmp;
    tmp.x = this->x - other.x;
    tmp.y = this->y - other.y;
    return tmp;
}

V V::operator+(const V& other) {
    V tmp;
    tmp.x = this->x + other.x;
    tmp.y = this->y + other.y;
    return tmp;
}
//V V::operator*(const V& other) {
//    V tmp;
//    tmp.x = this->x * other.x;
//    tmp.y = this->y * other.y;
//    return tmp;
//}

double V::operator<<(const V &other)
{
    return this->x * other.x + this->y * other.y;
}
V& V::operator*=(double value) {
    this->x *= value;
    this->y *= value;
    return *this;
}

bool V::operator<(const V &other)
{
    return true;
}

bool V::operator==(const V &other)
{
    return this->x==other.x&&this->y==other.y;
}

QPair<V,V> V::makeProection(double pointX, double pointY)
{
        V v01; //скорость шара this в проекции на прямую через центры шаров this и other
        v01.x = (this->x * pointX / pointY + this->y) / (pointX / pointY + pointY / pointX);//см документацию
        v01.y = v01.x * pointY / pointX;
        V v01_Per;
        v01_Per.x = (this->x * pointX / pointY - this->y) / (pointX / pointY + pointY / pointX);
        v01_Per.y = -pointX/pointY*v01_Per.x;

        return qMakePair(v01,v01_Per);
}

QPair<V, V> V::makeProection(Coord coord)
{
    double pointX = coord.x;
    double pointY = coord.y;
    V v01;      //скорость шара this в проекции на прямую через центры шаров this и other
    v01.x = (this->x * pointX / pointY + this->y) / (pointX / pointY + pointY / pointX);        //см документацию
    v01.y = v01.x * pointY / pointX;
    V v01_Per=*this-v01;
//    v01_Per.x = (this->x * pointX / pointY - this->y) / (pointX / pointY + pointY / pointX);
//    v01_Per.y = -pointX/pointY*v01_Per.x;

    return qMakePair(v01,v01_Per);
}

V V::makeRhombProection(Coord firstCoord, Coord secondCoord)
{
    V Vtmp;
    Vtmp.x = (this->y - this->x * secondCoord.y / secondCoord.x) / (firstCoord.y / firstCoord.x - secondCoord.y / secondCoord.x); //см документацию
    Vtmp.y = (firstCoord.y / firstCoord.x * Vtmp.x);
    return Vtmp;
}



V V::addTwoVector(QPair<V, V> pair)
{
    return V(pair.first.x + pair.second.x, pair.first.y + pair.second.y);
}

double V::vectorLenghtSquare()
{
    return x*x+y*y;
}

bool V::isNull()
{
        return abs(x)<MainWindow::deltaVmin && abs(y)<MainWindow::deltaVmin;
}


