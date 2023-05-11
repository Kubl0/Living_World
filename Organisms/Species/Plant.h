#pragma once

#include "Organism.h"

class Plant : public Organism {
public:
    Plant(Position position);

    void move(int dx, int dy);

    Organism* consequence(Organism* org1, Organism* org2);

    virtual Plant* clone(Position position) = 0;
};
