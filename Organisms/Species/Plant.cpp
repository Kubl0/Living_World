#include <iostream>
#include "Plant.h"

Plant::Plant(Position position) : Organism(position) {
    setSpecies("P");
}

void Plant::move(int dx, int dy) {
    Organism::move(0, 0);
}
