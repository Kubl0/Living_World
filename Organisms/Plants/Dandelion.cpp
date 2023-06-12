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
    Dandelion* dandelion = new Dandelion(position);
    dandelion->setAncestors(getAncestors());
    return dandelion;
}