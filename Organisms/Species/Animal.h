#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(Position position);

    void move(int dx, int dy);

    shared_ptr<Organism> consequence(shared_ptr<Organism> org1, shared_ptr<Organism> org2);

    virtual Animal* clone(Position position) = 0;

    bool isToxic();

};
