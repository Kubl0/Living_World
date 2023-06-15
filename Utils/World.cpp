#include <algorithm>
#include <iostream>
#include <cmath>
#include "World.h"
#include "Organisms/Animals/Wolf.h"
#include "Organisms/Animals/Sheep.h"
#include "Organisms/Plants/Dandelion.h"
#include "Organisms/Plants/Toadstool.h"
#include "Organisms/Plants/Grass.h"
#include <fstream>

World::World(int width, int height) {
    setWidth(width);
    setHeight(height);
}

void World::addOrganism(shared_ptr<Organism> organism) {
    organism->setBorn(getTurn());
    organisms.emplace_back(organism);
}

int World::getWidth() {
    return this->width;
}

void World::setWidth(int w) {
    this->width = w;
}

int World::getHeight() {
    return this->height;
}

void World::setHeight(int h) {
    this->height = h;
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
    for (shared_ptr<Organism> org: organisms)
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
        }
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
        if (org->getLifetime() - 1 <= 0) {
            cout << org->getSpecies() << org->getPosition().toString() << " died" << endl;
            for (shared_ptr<Organism> organism : organisms) {
                if (organism->getSpecies() == org->getSpecies()) {
                    organism->addAncestor(org->getBorn(), turn);
                }
            }
            it = organisms.erase(it);
            continue;
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

        if (numberOfNeighboringOrganisms > 0) {
            int random = rand() % numberOfNeighboringOrganisms;
            shared_ptr<Organism> orgToFight = getOrgFromPosition(neighboringOrganisms[random]);
            shared_ptr<Organism> beatenOrganism = org->consequence(org, orgToFight);
            if (beatenOrganism != nullptr) {
                if (org != beatenOrganism) {
                    cout << org->getSpecies() << " beat " << beatenOrganism->getSpecies() << endl;
                } else {
                    cout << orgToFight->getSpecies() << " beat " << org->getSpecies() << endl;
                }
                if (orgToFight->isToxic()) {
                    cout << org->getSpecies() << " will die from poisoning soon" << endl;
                    org->setLifetime(2);
                    org->setPower(0);
                }
                for (shared_ptr<Organism> orgs: organisms) {
                    if (orgs->getSpecies() == beatenOrganism->getSpecies()) {
                        orgs->addAncestor(beatenOrganism->getBorn(), turn);
                    }
                }
                organisms.erase(remove(organisms.begin(), organisms.end(), beatenOrganism), organisms.end());
            }
        }
    }

    for (shared_ptr<Organism> org: organisms) {
        cout << org->toString() << endl;
    }

    //Add new organisms
    for (Organism *org: newOrganisms) {
        org->setBorn(getTurn());
        organisms.emplace_back(org);
    }
    turn++;
}

shared_ptr<Organism> World::getOrgFromPosition(Position position) {
    for (shared_ptr<Organism> org: organisms)
        if (org->getPosition().getX() == position.getX() && org->getPosition().getY() == position.getY())
            return org;
    return nullptr;
}

vector<Position> World::filterSpecies(vector<Position> positions, const string &species) {
    auto iter = remove_if(positions.begin(), positions.end(),
                          [this, species](Position pos) {
                              return getOrgFromPosition(pos)->getSpecies() == species;
                          });
    positions.erase(iter, positions.end());
    return positions;
}

void World::writeWorld(const string& fileName) {
    fstream my_file;
    my_file.open(fileName, ios::out | ios::binary);
    if (my_file.is_open()) {
        my_file.write((char *) &this->width, sizeof(int));
        my_file.write((char *) &this->height, sizeof(int));
        my_file.write((char *) &this->turn, sizeof(int));
        int orgs_size = this->organisms.size();
        my_file.write((char *) &orgs_size, sizeof(int));
        for (int i = 0; i < orgs_size; i++) {
            int data;
            data = this->organisms[i]->getPower();
            my_file.write((char *) &data, sizeof(int));
            data = this->organisms[i]->getPosition().getX();
            my_file.write((char *) &data, sizeof(int));
            data = this->organisms[i]->getPosition().getY();
            my_file.write((char *) &data, sizeof(int));
            string s_data = this->organisms[i]->getSpecies();
            int s_size = s_data.size();
            my_file.write((char *) &s_size, sizeof(int));
            my_file.write(s_data.data(), s_data.size());
        }
        my_file.close();
    }
}

void World::readWorld(const string& fileName) {
    fstream my_file;
    my_file.open(fileName, ios::in | ios::binary);
    if (my_file.is_open()) {
        int result;
        my_file.read((char *) &result, sizeof(int));
        this->width = (int) result;
        my_file.read((char *) &result, sizeof(int));
        this->height = (int) result;
        my_file.read((char *) &result, sizeof(int));
        this->turn = (int) result;
        my_file.read((char *) &result, sizeof(int));
        int orgs_size = (int) result;
        vector<shared_ptr<Organism>> new_organisms;
        for (int i = 0; i < orgs_size; i++) {
            my_file.read((char *) &result, sizeof(int));
            int pos_x;
            my_file.read((char *) &result, sizeof(int));
            pos_x = (int) result;
            int pos_y;
            my_file.read((char *) &result, sizeof(int));
            pos_y = (int) result;
            Position pos{pos_x, pos_y};

            int s_size;
            my_file.read((char *) &result, sizeof(int));
            s_size = (int) result;

            string species;
            species.resize(s_size);
            my_file.read((char *) &species[0], s_size);

            switch (species[0]) {
                case 'S':
                    new_organisms.push_back(make_shared<Sheep>(pos));
                    break;
                case 'W':
                    new_organisms.push_back(make_shared<Wolf>(pos));
                    break;
                case 'D':
                    new_organisms.push_back(make_shared<Dandelion>(pos));
                    break;
                case 'G':
                    new_organisms.push_back(make_shared<Grass>(pos));
                    break;
                case 'T':
                    new_organisms.push_back(make_shared<Toadstool>(pos));
                    break;
            }
        }
        setOrganisms(new_organisms);
        my_file.close();
    }
}

void World::setOrganisms(vector<shared_ptr<Organism>> newOrgs) {
    this->organisms = newOrgs;
}



