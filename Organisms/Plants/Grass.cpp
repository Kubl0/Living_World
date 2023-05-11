#include "Grass.h"

Grass::Grass(Position position) : Plant(position)
{
    setSpecies("G");
    setPower(1);
    setLifetime(5);
    setPowerToReproduce(3);
}

Grass* Grass::clone(Position position)
{
    return new Grass(position);
}
