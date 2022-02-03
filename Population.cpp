#include "Population.hpp"

Population::Population() : nmutation(0), pmutation(20) {}

Population::Population(Tour baseTour) : nmutation(0), pmutation(20) {
    int sal, index;
    std::vector<int> salesmen;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        Tour tour;
        index = 0;
        tour.setTour(baseTour.getTour());
        for(int j = 0; j < SALESMEN_NUMBER; j++) {
            if(j == SALESMEN_NUMBER - 1) {
                salesmen.push_back(CITIES_NUMBER - index);
                break;
            }
            sal = rand() % (CITIES_NUMBER - index) + 1;
            while(index + sal >= CITIES_NUMBER - (SALESMEN_NUMBER - j))
                sal = rand() % (CITIES_NUMBER - index + 1) + 1;
            salesmen.push_back(sal);
            index += sal;
        }
        tour.setSalesmen(salesmen);
        tour.changeOrder();
        tour.setFitness();
        tour.setDistance();
        tours.push_back(tour);
     }
}

Tour Population::getTour(int index) { return tours[index]; }

std::vector<Tour> Population::getTours() { return tours; }

int Population::getSize() { return POPULATION_SIZE; }

inline double Population::getBestDistance() { return getBestTour().getTourDistance(); }

Tour Population::getBestTour() {
    Tour best(tours[0]);
    for (auto it = tours.begin() + 1; it < tours.end(); it++) {
        if (best.getTourDistance() > it->getTourDistance()) {
            best = *it;
        }
    }
    return best;
}

void Population::setTours(const std::vector<Tour> tours) { Population::tours = tours; }

inline int Population::getNmutation() { return nmutation; }

void Population::incNmutation() { nmutation++; setPmutation(); }

void Population::delNmutation() { nmutation = 0; setPmutation(); }

void Population::setPmutation() { 
    if(nmutation == 0)
        pmutation = 20;
    else if (nmutation < 2)
        pmutation = 17;
    else if (nmutation < 5)
        pmutation = 13;
    else if (nmutation < 10)
        pmutation = 10;
    else 
        pmutation = 5;
}

int Population:: getPmutation() { return pmutation; }

Population& Population::operator = (Population& p){
    tours = p.getTours();
    nmutation = p.nmutation;
    pmutation = p.pmutation;
    return *this;
}
