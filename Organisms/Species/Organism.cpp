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