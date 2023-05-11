#include "Sheep.h"

Sheep::Sheep(Position position) : Animal(position)
{
    setSpecies("S");
    setPower(5);
    setLifetime(15);
    setPowerToReproduce(9);
}

Sheep* Sheep::clone(Position position)
{
    return new Sheep(position);
}