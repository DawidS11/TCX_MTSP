#pragma once
#include <iostream>

#include "Tour.hpp"

class Population {
private:
    constexpr static int SWAPS_NUMBER = 100;
    std::vector<Tour> tours;
    int nmutation, pmutation;

public:
    Population();
    Population(Tour baseTour);
    
    Tour getTour(int index);
    std::vector<Tour> getTours();
    int getSize();
    inline double getBestDistance();
    Tour getBestTour();
    void setTours(const std::vector<Tour> tours);
    inline int getNmutation();
    void incNmutation();
    void delNmutation();
    void setPmutation();
    int getPmutation();
    Population& operator = (Population& p);
};
