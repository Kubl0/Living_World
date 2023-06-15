#include <iostream>
#include "Animal.h"

Animal::Animal(Position position) : Organism(position) {
    setSpecies("P");
}

void Animal::move(int dx, int dy) {
    Organism::move(dx, dy);
}

shared_ptr<Organism> Animal::consequence(shared_ptr<Organism> org1, shared_ptr<Organism> org2) {
    if(org1->getPower()>org2->getPower()) {
        return org2;
    } else {
        return org1;
    }
}

bool Animal::isToxic() {
    return false;
}

