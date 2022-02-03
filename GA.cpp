#include "GA.hpp"

std::vector<Tour> GA::select(Population& p) {
    std::vector<Tour> parents;
    std::vector<double> probability;
    std::vector<Tour> tempTours = p.getTours();

    std::sort(tempTours.begin(), tempTours.end());                              // Sortuje od najkrotszego dystansu, żeby najlepsze jednostki były na początku.

    double totalFitness = 0.0;
    double offset = 0.0;
    int j = 0, index = 0, index2 = 0;
    for(j = 0; j < p.getSize(); j++)
        totalFitness += tempTours[j].getFitness();
    for(j = 0; j < p.getSize(); j++)
        probability.push_back(tempTours[j].getFitness() / totalFitness);

    double r = (double)rand() / RAND_MAX;
    double r2 = 1 - r;
    index = 0;
    while(offset > r && index < p.getSize() - 1) {
        offset += probability[index];
        index++;
    }
    parents.push_back(tempTours[index]);
    index2 = 0;
    offset = 0.0;
    while(offset > r2 && index2 < p.getSize() - 1) {
        offset += probability[index2];
        index2++;
    }
    if(index == index2) {                                                       // Jesli wylosuje tych samych rodzicow.
        if(index2 > 0)
            index2--;
        else
            index2++;
    }
    parents.push_back(tempTours[index2]); 
    return parents;
} 

bool GA::flip(Population& p) {                      
    int r = rand() % 99 + 1;
    if(r <= p.getPmutation())
        return true;
    return false;
}

void GA::mutation(Population& p, Tour& t) {
    bool mutate = flip(p);
    if(mutate) {
        p.incNmutation();
        int r = rand() % CITIES_NUMBER;
        int r2 = rand() % CITIES_NUMBER;
        while(r == r2) {
            r2 = rand() % CITIES_NUMBER;
        }
        t.swapCities(r, r2);

        r = rand() % SALESMEN_NUMBER;
        r2 = rand() % SALESMEN_NUMBER;
        while(r == r2) {
            r2 = rand() % SALESMEN_NUMBER;
        }
        t.swapSalesmen(r, r2);
    }
}

Tour GA::tcx(Tour t1, Tour t2) {
    std::vector<City> parent1Cities = t1.getTour();
    std::vector<City> parent2Cities = t2.getTour();
    std::vector<int> parent1Sal = t1.getSalesmen();
    std::vector<int> parent2Sal = t2.getSalesmen();

    Tour child; 
    std::vector<City> childCities;
    std::vector<int> childSalesmen;
    int m = SALESMEN_NUMBER, i, k, index = 0, index2;
    int segment[m], segment2[m], starting[m], totalSavedGenes = 0, totalUnsavedGenes = 0;
    std::vector<City> savedGenesPool, unsavedGenesPool, unsavedGenesPool2;

    int segSum = 0;
    for(i = 0; i < m; i++) {
        segment[i] = rand() % parent1Sal[i] + 1;
        segSum += segment[i];
        while(segSum + m - i - 1 > CITIES_NUMBER) {
            segSum -= segment[i];
            segment[i] = rand() % parent1Sal[i] + 1;
            segSum += segment[i];
        }

        if(parent1Sal[i] > segment[i]) {
            starting[i] = rand() % (parent1Sal[i] - segment[i]) + index;
            for(k = starting[i]; k < starting[i] + segment[i]; k++) {
                savedGenesPool.push_back(parent1Cities[k]);
                totalSavedGenes++;
            }
        }
        else 
            for(k = index; k < index + segment[i]; k++) {
                savedGenesPool.push_back(parent1Cities[k]); 
                totalSavedGenes++;
            }
        index += parent1Sal[i];
    }

    totalUnsavedGenes = CITIES_NUMBER - totalSavedGenes;
    auto it = savedGenesPool.begin();
    for(i = 0; i < CITIES_NUMBER; i++) {                                                     
        it = std::find(savedGenesPool.begin(), savedGenesPool.end(), parent1Cities[i]);
        if(it == savedGenesPool.end()) 
            unsavedGenesPool.push_back(parent1Cities[i]);
    }

    for(k = 0; k < CITIES_NUMBER; k++) {
        for(i = 0; i < totalUnsavedGenes; i++) {
            if(unsavedGenesPool[i] == parent2Cities[k]) {
                unsavedGenesPool2.push_back(unsavedGenesPool[i]);
                break;
            }
        }
    }
    k = 0;
    segSum = 0;
    for(i = 0; i < m; i++) {
        if(i != m - 1) {
            if(segSum == totalUnsavedGenes)
                segment2[i] = 0;
            else
                segment2[i] = rand() % (totalUnsavedGenes - segSum) + 1;
            segSum += segment2[i];
        }
        else 
            segment2[i] = totalUnsavedGenes - segSum;
    }
    index = 0;
    index2 = 0;

    for(i = 0; i < m; i++) {
        for(k = index; k < index + segment[i]; k++) 
            childCities.push_back(savedGenesPool[k]);
        index += segment[i];
        for(k = index2; k < index2 + segment2[i]; k++) 
            childCities.push_back(unsavedGenesPool2[k]);
        index2 += segment2[i];
        childSalesmen.push_back(segment[i] + segment2[i]);
    }

    child.setTour(childCities);
    child.setSalesmen(childSalesmen);
    child.setFitness();
    child.setDistance(); 
    return child;
}

Tour GA::standard_crossover(Tour t1, Tour t2) {
    std::vector<City> parent1Cities = t1.getTour();
    std::vector<City> parent2Cities = t2.getTour();
    std::vector<int> parent1Sal = t1.getSalesmen();
    std::vector<int> parent2Sal = t2.getSalesmen();

    Tour child; 
    std::vector<City> childCities;
    std::vector<int> childSalesmen;

    int r = rand() % (CITIES_NUMBER - 1) + 1;
    int i;
    for (i = 0; i < r; i++) 
        childCities.push_back(parent1Cities[i]);

    i = 0;
    while (childCities.size() < CITIES_NUMBER) {
        auto it = std::find(childCities.begin(), childCities.end(), parent2Cities[i]);
        if(it == childCities.end()) 
            childCities.push_back(parent2Cities[i]);
        i++;
    }

    r = rand() % 2;
    if(r == 0)
        childSalesmen = parent1Sal;
    else
        childSalesmen = parent2Sal;
    child.setTour(childCities);
    child.setSalesmen(childSalesmen);
    child.setFitness();
    child.setDistance(); 
    return child;
}

void GA::evolution(Population& p, int crossover) {
    Population newPop;
    std::vector<Tour> newPopTours;              
    std::vector<Tour> parents(select(p));
    int i, j; 
    Tour child1, child2; 
    if(crossover == 0) {
        child1 = tcx(parents[0], parents[1]);
        child2 = tcx(parents[0], parents[1]);
    }
    else {
        child1 = standard_crossover(parents[0], parents[1]);
        child2 = standard_crossover(parents[0], parents[1]);
    }
    int r = rand() % p.getSize();
    int r2 = rand() % p.getSize();
    while(r == r2) {
        r2 = rand() % p.getSize();
    }

    for(int i = 0; i < p.getSize(); i++) {
        if(i == r)
            newPopTours.push_back(child1);
        else if(i == r2)
            newPopTours.push_back(child2);
        else
            newPopTours.push_back(p.getTour(i));      
    }

    mutation(p, newPopTours[r]);
    mutation(p, newPopTours[r2]);
    newPopTours[r].setDistance();
    newPopTours[r].setFitness();
    newPopTours[r2].setDistance();
    newPopTours[r2].setFitness();
    newPop.setTours(newPopTours);
    p = newPop;
}

void GA::optimization(Population& p, int crossover) {
    std::cout << "Poczatkowy najkrotszy dystans: " <<
        p.getBestTour().getTourDistance() << std::endl;
    std::cout << "============================================\n";

    for(int i = 0; i < ITERATIONS; i++) {
        evolution(p, crossover);
        if(i == 99 || i == 499 || i == 999) {
            std::cout << "\nNajkrotszy dystans po " << i + 1 << " iteracjach: " << p.getBestTour().getTourDistance() << std::endl;
            p.delNmutation();
        }
    }

    std::cout << "\n============================================" << std::endl;
}
