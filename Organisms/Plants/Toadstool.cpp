#include "Toadstool.h"

Toadstool::Toadstool(Position position) : Plant(position)
{
    setSpecies("T");
    setPower(1);
    setLifetime(5);
    setPowerToReproduce(4);
}

Toadstool* Toadstool::clone(Position position)
{
    return new Toadstool(position);
}
