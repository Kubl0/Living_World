#pragma once

#include "Organism.h"

class Plant : public Organism {
public:
    Plant(Position position);

    void move(int dx, int dy);

    shared_ptr<Organism> consequence(shared_ptr<Organism> org1, shared_ptr<Organism> org2);

    bool isToxic();

    virtual Plant* clone(Position position) = 0;
};
