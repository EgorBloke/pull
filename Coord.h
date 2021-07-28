#ifndef COORD_H
#define COORD_H
class Coord {
public:
    Coord(double x = 0., double y = 0.)
    {
        this->x = x;
        this->y = y;
    }
    double x;
    double y;
public:
    Coord operator+ (const Coord& other) const;
    Coord operator*(const int val)const;
    bool operator==(const Coord& other);
    bool operator<(const Coord& other);
    bool operator>(const Coord& other);

};
#endif // COORD_H
