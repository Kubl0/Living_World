#include <iostream>
#include "Organisms/Species/Organism.h"
#include "Organisms/Species/Plant.h"
#include "Utils/World.h"
#include "Organisms/Plants/Grass.h"
#include "Organisms/Plants/Dandelion.h"
#include "Organisms/Plants/Toadstool.h"
#include "Organisms/Animals/Sheep.h"
#include "Organisms/Animals/Wolf.h"

int main() {
    World world(5,5);
    Grass grass(Position(0,0));
    Dandelion dandelion(Position(1,1));
    Toadstool toadstool(Position(2,2));
    world.addOrganism(&grass);
    world.addOrganism(&dandelion);
    world.addOrganism(&toadstool);

    Sheep sheep(Position(3,3));
    Wolf wolf(Position(4,4));
    world.addOrganism(&sheep);
    world.addOrganism(&wolf);

    cout << world.toString();

    for (int i = 0; i < 100; i++) {
        cin.ignore();
        system("cls");
        world.makeTurn();
        cout << world.toString();
    }
}
