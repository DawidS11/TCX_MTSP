#pragma once
#include <iostream>
#include <vector>

#include "Population.hpp"

class GA {
private:
    constexpr static int ITERATIONS = 1000;
    
public:
    std::vector<Tour> select(Population& p);
    bool flip(Population& p);
    void mutation(Population& p, Tour& t);
    Tour tcx(Tour t1, Tour t2);
    Tour standard_crossover(Tour t1, Tour t2);      
    void evolution(Population& p, int crossover);   // crossover == 0 -> tcx, crossover == 1 -> standard
    void optimization(Population& p, int crossover);
};
