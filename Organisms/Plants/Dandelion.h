#include "Utils/Position.h"
#include "Organisms/Species/Plant.h"

class Dandelion : public Plant{
public:
    Dandelion(Position position);

    Dandelion* clone(Position position);
};

