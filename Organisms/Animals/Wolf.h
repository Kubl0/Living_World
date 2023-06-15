#include "Utils/Position.h"
#include "Organisms/Species/Animal.h"
#include <iostream>

class Wolf : public Animal{
public:
    Wolf(Position position);
    ~Wolf(){
        std::cout<<this->getPosition().toString()<<"Wolf destroyed. Adress: "<<this<<std::endl;
    }

    Wolf* clone(Position position);
};

