#include <iostream>
#include "Organism.h"

Organism::Organism(Position position) {
    this->position = position;
    setSpecies("O");
}

int Organism::getPower() {
    return power;
}

void Organism::setPower(int power) {
    this->power = power;
}

string Organism::getSpecies() {
    return species;
}

void Organism::setSpecies(string spec) {
    species = spec;
}

Position Organism::getPosition() {
    return position;
}

void Organism::setPosition(Position position) {
    this->position = position;
}

string Organism::toString() {
    return "{ species: " + getSpecies() +
           ", power: " + to_string(getPower()) +
           ", position: " + getPosition().toString() +
           ", powerToReproduce: " + to_string(getPowerToReproduce()) +
           ", lifeTime: " + to_string(getLifetime()) +
           ", born: " + to_string(getBorn()) +
           " ancestors: " + printAncestors() +
           " }";
}

string Organism::printAncestors() {
    string result = "";
    for (int i = 0; i < 1000; ++i) {
        if (ancestors[i][0] != 0) {
            result += to_string(ancestors[i][0]) + " " + to_string(ancestors[i][1]) + ", ";
        }
    }
    return result;
}

array<array<int, 2>, 1000> Organism::getAncestors() {
    return ancestors;
}

void Organism::setAncestors(array<array<int, 2>, 1000> ancestors) {
    this->ancestors = ancestors;
}

void Organism::addAncestor(int born, int died) {
    for (int i = 0; i < 1000; ++i) {
        if (ancestors[i][0] == 0) {
            ancestors[i][0] = born;
            ancestors[i][1] = died;
            break;
        }
    }
}

int Organism::getPowerToReproduce() {
    return powerToReproduce;
}

void Organism::setPowerToReproduce(int powerToReproduce) {
    this->powerToReproduce = powerToReproduce;
}

int Organism::getLifetime() {
    return lifeTime;
}

void Organism::setLifetime(int lifetime) {
    this->lifeTime = lifetime;
}

void Organism::move(int dx, int dy) {
    this->position.setX(this->position.getX() + dx);
    this->position.setY(this->position.getY() + dy);
}

int Organism::getBorn() {
    return born;
}

void Organism::setBorn(int born) {
    this->born = born;
}




