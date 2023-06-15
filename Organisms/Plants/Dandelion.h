#include "Utils/Position.h"
#include "Organisms/Species/Plant.h"
#include <iostream>

class Dandelion : public Plant{
public:
    Dandelion(Position position);
    ~Dandelion(){
        std::cout<<this->getPosition().toString()<<"Dandelion destroyed. Adress: "<<this<<std::endl;
    }

    Dandelion* clone(Position position);
};

