#include <iostream>
#include "Plant.h"

Plant::Plant(Position position) : Organism(position) {
    setSpecies("P");
}

void Plant::move(int dx, int dy) {
    Organism::move(0, 0);
}

shared_ptr<Organism> Plant::consequence(shared_ptr<Organism> org1, shared_ptr<Organism> org2) {
    return nullptr;
}

bool Plant::isToxic() {
    return false;
}
