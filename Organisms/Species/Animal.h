#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(Position position);

    void move(int dx, int dy);

    virtual Animal* clone(Position position) = 0;
};
