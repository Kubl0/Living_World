#include <iostream>
#include "Utils/World.h"
#include "Organisms/Plants/Grass.h"
#include "Organisms/Plants/Dandelion.h"
#include "Organisms/Plants/Toadstool.h"
#include "Organisms/Animals/Sheep.h"
#include "Organisms/Animals/Wolf.h"

int main() {
    World world(5,5);
    shared_ptr<Organism> grass = make_shared<Grass>(Position(0,0));
    shared_ptr<Organism> dandelion = make_shared<Dandelion>(Position(1,1));
    shared_ptr<Organism> toadstool = make_shared<Toadstool>(Position(2,2));
    world.addOrganism(grass);
    world.addOrganism(dandelion);
    world.addOrganism(toadstool);

    shared_ptr<Organism> sheep = make_shared<Sheep>(Position(3,3));
    shared_ptr<Organism> wolf = make_shared<Wolf>(Position(4,4));
    world.addOrganism(sheep);
    world.addOrganism(wolf);

    cout << world.toString();

    for (int i = 0; i < 100; i++) {
        cin.ignore();
        system("cls");
        world.makeTurn();
        cout << world.toString();
    }

//    world.makeTurn();
//    cout << world.toString() << endl;
//
//    world.writeWorld("world.bin");
//
//    // Tura 3
//    world.makeTurn();
//    cout << world.toString() << endl;
//
//    // powrot do Tury 2
//    world.readWorld("world.bin");
//    cout << world.toString() << endl;

}
