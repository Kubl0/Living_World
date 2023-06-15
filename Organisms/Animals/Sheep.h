#include "Utils/Position.h"
#include "Organisms/Species/Animal.h"

class Sheep : public Animal{
public:
    Sheep(Position position);
    ~Sheep();

    Sheep* clone(Position position);
};

