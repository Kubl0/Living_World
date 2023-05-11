#include "Utils/Position.h"
#include "Organisms/Species/Plant.h"

class Grass : public Plant{
public:
    Grass(Position position);

    Grass* clone(Position position);
};

