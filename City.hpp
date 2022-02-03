#pragma once
#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>

extern int POPULATION_SIZE;
extern int CITIES_NUMBER;
extern int SALESMEN_NUMBER;

class City {
private:  
    int number;
    int x, y;

public:
    City(int _number, int _x, int _y);
    City(City const& origin);

    inline int getX();
    inline int getY();
    int getNumber();
    double getDistance(City& c);
    bool operator == (const City& c) const;
};
