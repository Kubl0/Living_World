#include "Sheep.h"
#include <iostream>

Sheep::Sheep(Position position) : Animal(position)
{
    setSpecies("S");
    setPower(5);
    setLifetime(15);
    setPowerToReproduce(9);
}

Sheep::~Sheep(){
    cout<<this->getPosition().toString()<<"Sheep destroyed. Adress: "<<this<<endl;
}

Sheep* Sheep::clone(Position position)
{
    Sheep* sheep = new Sheep(position);
    sheep->setAncestors(getAncestors());
    return sheep;
}
