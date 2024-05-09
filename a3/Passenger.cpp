#include "Passenger.h"

Passenger::Passenger(int id) :  id(id), currentFloor(0), destinationFloor(-1), weight(100){
    qDebug()<<"Creating passenger "<<id;
}

Passenger::~Passenger(){}


// Randomly return true or false
bool Passenger::speak(){
    return QRandomGenerator::global()->generate() % 2 == 0;
}

// Passenger to handle obstruction
void Passenger::handleObstruction(){
    if(this->curElevator == nullptr){return;}
    this->curElevator->handleObstruction();
}

//void Passenger::embark(Elevator* elevator){}

//void Passenger::disembark(Elevator* elevator){}

void Passenger::pressHelp(){}

int Passenger::getID() const {
    return this->id;
}

int Passenger::getWeight() const{
    return this->weight;
}

int Passenger::getDest() const {
    return this->destinationFloor;
}

void Passenger::setElevator(Elevator* e){
    this->curElevator = e;
}

void Passenger::setFloor(Floor* f){
    this->curFloor = f;
}

void Passenger::setDest(int n){
    this->destinationFloor = n;
}

Floor* Passenger::getFloor() const {
    return this->curFloor;
}

Elevator* Passenger::getElevator() const {
    return this->curElevator;
}
