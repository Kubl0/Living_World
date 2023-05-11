#include "Utils/Position.h"
#include "Organisms/Species/Plant.h"

class Toadstool : public Plant{
public:
    Toadstool(Position position);

    Toadstool* clone(Position position);
};

