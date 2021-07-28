#include"Coord.h"

Coord Coord::operator+ (const Coord& other) const
{
    Coord tmp(this->x + other.x, this->y + other.y);
    return  tmp;
}

Coord Coord::operator*(const int val) const
{
    Coord tmp(this->x *val, this->y * val);
    return  tmp;
}

bool Coord::operator==(const Coord &other)
{
    return this->x==other.x&&this->y==other.y;
}

bool Coord::operator<(const Coord &other)
{
    return this->x<other.x&&this->y<other.y;
}

bool Coord::operator>(const Coord &other)
{
    return this->x>other.x&&this->y>other.y;
}


