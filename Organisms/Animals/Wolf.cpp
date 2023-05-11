#include "Wolf.h"

Wolf::Wolf(Position position) : Animal(position)
{
    setSpecies("W");
    setPower(10);
    setLifetime(18);
    setPowerToReproduce(15);
}

Wolf* Wolf::clone(Position position)
{
    return new Wolf(position);
}
