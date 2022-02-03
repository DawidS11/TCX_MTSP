#include "City.hpp"

int POPULATION_SIZE;
int CITIES_NUMBER;
int SALESMEN_NUMBER;

City::City(int _number, int _x, int _y) : number(_number), x(_x), y(_y) {}

City::City(City const& origin) : x(origin.x), y(origin.y), number(origin.number) {}

inline int City::getX() { return x; }

inline int City::getY() { return y; }

int City::getNumber() { return number; }

double City::getDistance(City& c) {
    int distX = abs(getX() - c.getX());
    int distY = abs(getY() - c.getY());
    return sqrt(pow((double)distX, 2) + pow((double)distY, 2));
}

bool City::operator == (const City& c) const {
    return (number == c.number) && (x == c.x) && (y == c.y);
}
