#include <iostream>
#include "Animal.h"

Animal::Animal(Position position) : Organism(position) {
    setSpecies("P");
}

void Animal::move(int dx, int dy) {
    Organism::move(dx, dy);
}

