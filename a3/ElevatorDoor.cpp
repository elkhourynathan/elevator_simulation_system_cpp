#include "ElevatorDoor.h"
#include "Elevator.h"

ElevatorDoor::ElevatorDoor(Elevator* elevator) :
    opened(false),
    obstructed(false),
    repeatedObstruction(0),
    elevator(elevator) {
}

ElevatorDoor::~ElevatorDoor() {
}

// Method to open elevator door
void ElevatorDoor::openDoor() {
    qDebug()<<"Elevator "<<this->elevator->getElevatorNum()<<" door opened";
    this->opened = true;
}

// Method to close elevator door
bool ElevatorDoor::closeDoor() {
    bool obstructed = this->checkObstruction();
    if(obstructed){
        qDebug()<<"Elevator "<<this->elevator->getElevatorNum()<<" is obstructed";
        this->repeatedObstruction += 1;
        if (this->repeatedObstruction > 2){
            this->elevator->updateDisplay("Handle the obstruction!");
            this->elevator->playAudio("Handle the obstruction");
        }
        return false;
    } else{
         qDebug()<<"Elevator "<<this->elevator->getElevatorNum()<<" door closed";
        this->repeatedObstruction = 0;
        this->opened = false;
        return true;
    }
}

// Method to check obstruction
bool ElevatorDoor::checkObstruction() {
    return this->obstructed;
}
