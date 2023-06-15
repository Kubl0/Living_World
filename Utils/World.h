#pragma once
#include <vector>
#include "Organisms/Species/Organism.h"
#include "Position.h"
#include <memory>

using namespace std;

class World {
private:
    int width;
    int height;
    int turn = 0;
    vector<shared_ptr<Organism>> organisms;

    bool isPositionOnWorld(int x, int y);
    bool isPositionFree(Position position);
    string getOrganismFromPosition(int x, int y);

public:
    World(int width, int height);
    World() : World(6, 6) {};

    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    int getTurn();

    void addOrganism(shared_ptr<Organism> organism);
    vector<Position> getVectorOfFreePositionsAround(Position position);
    vector<Position> filterPositionFromBorn(vector<Position> freePositions, vector<Organism*> newOrganisms);
    vector<Position> getNeighboringOrganisms(Position position);
    shared_ptr<Organism> getOrgFromPosition(Position position);


    void makeTurn();

    string toString();

    vector<Position> filterSpecies(vector<Position> positions, const string& species);

    void writeWorld(const string& fileName);

    void readWorld(const string& fileName);

    void setOrganisms(vector<shared_ptr<Organism>> newOrgs);
};

