#include "Utils/Position.h"
#include "Organisms/Species/Plant.h"
#include <iostream>

class Grass : public Plant{
public:
    Grass(Position position);
    ~Grass(){
        std::cout<<this->getPosition().toString()<<"Grass destroyed. Adress: "<<this<<std::endl;
    }

    Grass* clone(Position position);
};

