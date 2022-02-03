#include "Tour.hpp"

Tour::Tour() : distance(0.0), fitness(0.0) {}

bool Tour::base = false;
std::vector<City> Tour::baseCities;

Tour::Tour(Tour const& origin) : cities(origin.cities), salesmen(origin.salesmen), distance(origin.distance), fitness(origin.fitness) {}

void Tour::setDistance() { distance = getTourDistance(); }

void Tour::setFitness() { fitness = (1 / getTourDistance()) * 10000; }

double Tour::getTourDistance() {
    int i, s = 0, index = salesmen[0];
    double distance = 0.0;
    for(i = 0; i < CITIES_NUMBER; i++) {
        if(i == index - 1) {
            if(s == 0)
                distance += cities[index - 1].getDistance(cities[0]);
            else
                distance += cities[index - 1].getDistance(cities[index - salesmen[s]]);
            s++;
            index += salesmen[s];
        }
        else
            distance += cities[i].getDistance(cities[i + 1]);
    }
    return distance;
}

double Tour::getFitness() { return fitness; }

City& Tour::getCity(int position) { return cities[position]; }

int Tour::getSalesman(int position) { return salesmen[position]; }

std::vector<City> Tour::getTour() { return cities; }

std::vector<int> Tour::getSalesmen() { return salesmen; }

void Tour::setTour(std::vector<City> t) { cities = t; }

void Tour::setSalesmen(std::vector<int> s) { salesmen = s; }

bool Tour::containsCity(City c) {
    auto it = std::find(cities.begin(), cities.end(), c);
    return it != cities.end();
}

void Tour::swapCities(int c1, int c2) { std::swap(cities[c1], cities[c2]); }

void Tour::swapSalesmen(int c1, int c2) { std::swap(salesmen[c1], salesmen[c2]); }

void Tour::swapRandomCities() {
    int posA = rand() % CITIES_NUMBER, posB;
    int index = 0;
    for(int i = 0; i < SALESMEN_NUMBER; i++) {
        if(posA >= index && posA < index + salesmen[i]) {
            posB = rand() % salesmen[i] + index;
            std::swap(cities.at(posA), cities.at(posB));
            return;
        }
        index += salesmen[i];
    }
}

void Tour::swapRandomSalesmen() {
    int posA = rand() % SALESMEN_NUMBER;
    int posB = rand() % SALESMEN_NUMBER;
    std::swap(salesmen[posA], salesmen[posB]);                                  // Moga byc takie same, bo kolejnosc miast i tak zostanie zmieniona.
}

void Tour::changeOrder() {
    for(int i = 0; i < SWAPS_NUMBER; i++) {
        swapRandomCities();
        swapRandomSalesmen();
    }
}

bool Tour::operator == (Tour& t) {
    int i;
    for(i = 0; i < CITIES_NUMBER; i++)
        if(!(getCity(i) == t.getCity(i)))
            return false;
    for(i = 0; i < SALESMEN_NUMBER; i++)
        if(!((getSalesman(i)) == t.getSalesman(i)))
            return false;
    return true;
}

bool Tour::operator < (const Tour& t) const {
    return fitness > t.fitness;
}

bool Tour::operator > (const Tour& t) const {
    return fitness > t.fitness;
}

std::istream& operator >> (std::istream& is, Tour& tour) {
    std::vector<City> ccities;
    int number, x, y, i, j, sal = 0, index = 0;
    is >> POPULATION_SIZE >> CITIES_NUMBER >> SALESMEN_NUMBER;
    //std::cout << POPULATION_SIZE << "\n" << CITIES_NUMBER << "\n" << SALESMEN_NUMBER << "\n";

    for(j = 0; j < CITIES_NUMBER; j++) {
        is >> number >> x >> y;
        //std::cout << number << "  " << x << "  " << y << "\n";
        ccities.push_back(City(number, x, y));
    }
    tour.setTour(ccities);
    return is;
}
