#pragma once

#include <string>
#include "Utils/Position.h"

using namespace std;

class Organism {
private:
    int power;
    Position position;
    string species;
    int powerToReproduce;
    int lifeTime;

public:
    Organism(Position position);

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
    virtual Organism* consequence(Organism* org1, Organism* org2) = 0;
};
