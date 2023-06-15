#include "Utils/Position.h"
#include "Organisms/Species/Plant.h"
#include <iostream>

class Toadstool : public Plant{
public:
    Toadstool(Position position);
    ~Toadstool(){
        std::cout<<this->getPosition().toString()<<"Toadstool destroyed. Adress: "<<this<<std::endl;
    }

    Toadstool* clone(Position position);

    bool isToxic();
};

