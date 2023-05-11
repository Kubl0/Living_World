#include "Dandelion.h"

Dandelion::Dandelion(Position position) : Plant(position)
{
    setSpecies("D");
    setPower(1);
    setLifetime(7);
    setPowerToReproduce(5);
}

Dandelion* Dandelion::clone(Position position)
{
    return new Dandelion(position);
}
