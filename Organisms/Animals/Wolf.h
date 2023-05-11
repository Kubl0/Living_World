#include "Utils/Position.h"
#include "Organisms/Species/Animal.h"

class Wolf : public Animal{
public:
    Wolf(Position position);

    Wolf* clone(Position position);
};

