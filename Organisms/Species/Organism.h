#pragma once

#include <string>
#include <array>
#include <memory>
#include "Utils/Position.h"

using namespace std;

class Organism {
private:
    int power;
    Position position;
    string species;
    int powerToReproduce;
    int lifeTime;
    int born = 0;
    array<array<int, 2>, 1000> ancestors = {};


public:
    Organism(Position position);
    virtual ~Organism();

    int getBorn();
    void setBorn(int born);


    string getSpecies();
    void setSpecies(string spec);

    Position getPosition();
    void setPosition(Position position);

    int getPower();
    void setPower(int power);

    int getPowerToReproduce();
    void setPowerToReproduce(int powerToReproduce);

    int getLifetime();
    void setLifetime(int lifetime);

    string toString();

    virtual void move(int dx, int dy) = 0;
    virtual Organism* clone(Position position) = 0;
    virtual shared_ptr<Organism> consequence(shared_ptr<Organism> org1, shared_ptr<Organism> org2) = 0;
    virtual bool isToxic() = 0;

    array<array<int, 2>, 1000> getAncestors();
    void setAncestors(array<array<int, 2>, 1000> ancestors);
    string printAncestors();
    void addAncestor(int born, int died);
};
