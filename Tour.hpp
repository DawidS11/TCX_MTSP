#pragma once
#include <iostream>
#include <vector>

#include "City.hpp"

class Tour
{
private:
    constexpr static int SWAPS_NUMBER = 50;
    static std::vector<City> baseCities;
    static bool base;
    std::vector<City> cities;                             // Kazdy Tour ma wektor miast ustawianych w odpowiedniej kolejnosci
    std::vector<int> salesmen;                            // oraz wektor sprzedawcow, mowiacy ile ma miast i w ten sposob "rozdzielajacy" wektor miast. 
    double fitness;
    double distance;

public:
    Tour();
    Tour(Tour const& origin);
    ~Tour() = default;
    
    void setDistance();
    void setFitness();
    double getTourDistance();
    double getFitness();
    City& getCity(int position);
    int getSalesman(int position);
    std::vector<City> getTour();
    std::vector<int> getSalesmen();
    void setTour(std::vector<City> t);
    void setSalesmen(std::vector<int> s);
    bool containsCity(City c);
    void swapCities(int c1, int c2);
    void swapSalesmen(int c1, int c2);
    void swapRandomCities();            // funkcja do changeOrder
    void swapRandomSalesmen();          // funkcja do changeOrder
    void changeOrder();                 // funkcja do tworzenia nowej populacji
    bool operator == (Tour& t);
    bool operator<(const Tour& t) const;
    bool operator>(const Tour& t) const;
    friend std::istream& operator >> (std::istream& is, Tour& t);
};
