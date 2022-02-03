#include <iostream>
#include <fstream>

#include "GA.hpp"


int main(int argc, char *argv[]) {
    Tour baseTour;
    std::ifstream file("./data/100_50_20.txt");
    if(file.is_open())
        std::cout << "Udany odczyt danych z pliku\n\n";
    else {
        std::cout << "Nie udalo sie otworzyc pliku\n\n";
        return 1;
    }

    while(!file.eof()) 
        file >> baseTour;
    file.close();

    Population population(baseTour);
    GA ga;
    ga.optimization(population, 1);             // 0 dla tcx, 1 dla standard
}

