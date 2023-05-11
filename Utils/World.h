#pragma once
#include <vector>
#include "Organisms/Species/Organism.h"
#include "Position.h"

using namespace std;

class World {
private:
    int width;
    int height;
    int turn = 0;
    vector<Organism*> organisms;

    bool isPositionOnWorld(int x, int y);
    bool isPositionFree(Position position);
    string getOrganismFromPosition(int x, int y);

public:
    World(int width, int height);
    World() : World(6, 6) {};

    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    int getTurn();

    void addOrganism(Organism* organism);
    vector<Position> getVectorOfFreePositionsAround(Position position);
    vector<Position> filterPositionFromBorn(vector<Position> freePositions, vector<Organism*> newOrganisms);

    void makeTurn();

    string toString();

};

