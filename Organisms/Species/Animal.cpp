#include <iostream>
#include "Animal.h"

Animal::Animal(Position position) : Organism(position) {
    setSpecies("P");
}

void Animal::move(int dx, int dy) {
    Organism::move(dx, dy);
}

Organism* Animal::consequence(Organism* org1, Organism* org2) {
    if(org1->getPower()>org2->getPower()) {
        return org2;
    } else {
        return org1;
    }
}

