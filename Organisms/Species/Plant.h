#pragma once

#include "Organism.h"

class Plant : public Organism {
public:
    Plant(Position position);

    void move(int dx, int dy);

    virtual Plant* clone(Position position) = 0;
};
