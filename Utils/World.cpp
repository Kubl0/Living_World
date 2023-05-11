#include <algorithm>
#include <iostream>
#include <cmath>
#include "World.h"

World::World(int width, int height) {
    setWidth(width);
    setHeight(height);
}

void World::addOrganism(Organism *organism) {
    organisms.push_back(organism);
}

int World::getWidth() {
    return this->width;
}

void World::setWidth(int width) {
    this->width = width;
}

int World::getHeight() {
    return this->height;
}

void World::setHeight(int height) {
    this->height = height;
}

int World::getTurn() {
    return this->turn;
}

bool World::isPositionOnWorld(int x, int y) {
    return (x >= 0 && y >= 0 && x < getWidth() && y < getHeight());
}

bool World::isPositionFree(Position position) {
    return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

string World::getOrganismFromPosition(int x, int y) {
    for (Organism *org: organisms)
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org->getSpecies();
    return "";
}

vector<Position> World::filterPositionFromBorn(vector<Position> freePositions, vector<Organism *> newOrganisms) {
    for (auto &newOrg: newOrganisms) {
        auto iter = remove_if(freePositions.begin(), freePositions.end(),
                              [newOrg](Position pos) {
                                  return pos.getX() == newOrg->getPosition().getX() &&
                                         pos.getY() == newOrg->getPosition().getY();
                              });
        freePositions.erase(iter, freePositions.end());
    }

    return freePositions;
}

vector<Position> World::getVectorOfFreePositionsAround(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    vector<Position> result;
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) &&
                isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = remove_if(result.begin(), result.end(),
                          [this](Position pos) { return !isPositionFree(pos); });
    result.erase(iter, result.end());

    return result;
}

vector<Position> World::getNeighboringOrganisms(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    vector<Position> result;
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) &&
                isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = remove_if(result.begin(), result.end(),
                          [this](Position pos) { return getOrganismFromPosition(pos.getX(), pos.getY()).empty(); });
    result.erase(iter, result.end());
    return result;
}

string World::toString() {
    string result = "\nturn: " + to_string(getTurn()) + "\n";
    string spec;

    for (int wY = 0; wY < getHeight(); ++wY) {
        for (int wX = 0; wX < getWidth(); ++wX) {
            spec = getOrganismFromPosition(wX, wY);
            if (spec != "")
                result += spec;
            else
                result += ".";
        };
        result += "\n";
    }
    return result;
}

void World::makeTurn() {
    vector<Position> freePositions;
    int numberOfPositions;
    int randomIdx;
    vector<Organism *> newOrganisms;

    srand(time(NULL));
    for (auto it = organisms.begin(); it != organisms.end();) {
        auto &org = *it;

        //Check age
        if (org->getLifetime() - 1 == 0) {
            cout << org->getSpecies() << org->getPosition().toString() << " died" << endl;
            it = organisms.erase(it);
        } else {
            org->setLifetime(org->getLifetime() - 1);
            ++it;
        }

        //Move
        freePositions = getVectorOfFreePositionsAround(org->getPosition());
        freePositions = filterPositionFromBorn(freePositions, newOrganisms);
        numberOfPositions = freePositions.size();
        if (numberOfPositions > 0) {
            randomIdx = rand() % numberOfPositions;
            org->move(freePositions[randomIdx].getX() - org->getPosition().getX(),
                      freePositions[randomIdx].getY() - org->getPosition().getY());
        }

        //Add power
        org->setPower(org->getPower() + 1);

        //Reproduce
        if (org->getPower() >= org->getPowerToReproduce()) {
            freePositions = getVectorOfFreePositionsAround(org->getPosition());
            freePositions = filterPositionFromBorn(freePositions, newOrganisms);

            numberOfPositions = freePositions.size();

            if (numberOfPositions > 0) {
                randomIdx = rand() % freePositions.size();
                cout << org->getSpecies() << " born at " << freePositions[randomIdx].toString() << endl;
                Organism *newOrg = org->clone(freePositions[randomIdx]);
                newOrganisms.push_back(newOrg);
                org->setPower(org->getPower() / 2);
            }
        }

        //Fight if possible
        vector<Position> neighboringOrganisms = getNeighboringOrganisms(org->getPosition());
        neighboringOrganisms = filterSpecies(neighboringOrganisms, org->getSpecies());
        int numberOfNeighboringOrganisms = neighboringOrganisms.size();

        if(numberOfNeighboringOrganisms > 0){
            int random = rand() % numberOfNeighboringOrganisms;
            Organism* orgToFight = getOrgFromPosition(neighboringOrganisms[random]);
            Organism* beatenOrganism = org->consequence(org, orgToFight);
            if(beatenOrganism != nullptr){
                if(org != beatenOrganism){
                    cout << org->getSpecies() << " beat " << beatenOrganism->getSpecies() << endl;}
                else{
                    cout<< orgToFight->getSpecies() << " beat " << org->getSpecies() << endl;
                }
                organisms.erase(remove(organisms.begin(), organisms.end(), beatenOrganism), organisms.end());
            }
        }
    }

    organisms.insert(organisms.end(), newOrganisms.begin(), newOrganisms.end());
    turn++;
}

Organism* World::getOrgFromPosition(Position position){
    for (Organism *org: organisms)
        if (org->getPosition().getX() == position.getX() && org->getPosition().getY() == position.getY())
            return org;
    return nullptr;
}

vector<Position> World::filterSpecies(vector<Position> positions, string species){
    auto iter = remove_if(positions.begin(), positions.end(),
                          [this, species](Position pos) {
                              return getOrgFromPosition(pos)->getSpecies() == species;
                          });
    positions.erase(iter, positions.end());
    return positions;
}



