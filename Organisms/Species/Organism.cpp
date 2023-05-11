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
           "}";
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


string Organism::printAncestors() {
    string result = "";
    for (auto & ancestor : ancestors) {
        if (ancestor[1] == 0) {
            break;
        }
        result += "Born: " + to_string(ancestor[0]) + " Died: " + to_string(ancestor[1]) + "\n";
    }
    return result;
}

void Organism::addAncestors(int born, int died) {
    for (auto & ancestor : ancestors) {
        if (ancestor[0] == 0) {
            ancestor[0] = born;
            ancestor[1] = died;
            break;
        }
    }
}

array<array<int, 2>, 1000> Organism::cloneAncestors() {
    return ancestors;
}

void Organism::setAncestors(array<array<int, 2>, 1000> ancestors) {
    this->ancestors = ancestors;
}


