#include "ElevatorPanel.h"
#include "Elevator.h"

ElevatorPanel::ElevatorPanel(Elevator* elevator) : floor(0), visualMessage("Default"), elevator(elevator) {
}

ElevatorPanel::~ElevatorPanel() {
}

// Method to handle help press
void ElevatorPanel::help() {
    this->elevator->help();
}

// Method to open elevator door
void ElevatorPanel::manualOpen() {
    qDebug()<<"Elevator "<<this->elevator->getElevatorNum()<<" manual open pressed";
    this->elevator->openDoor();
}

// Method to close elevator door
void ElevatorPanel::manualClose() {
    qDebug()<<"Elevator "<<this->elevator->getElevatorNum()<<" manual close pressed";
    this->elevator->closeDoor();
}

// Method takes in Passenger* p and floorNumber and updates passenger and elevator with request
void ElevatorPanel::addStop(Passenger* p, int floorNumber) {
    p->setDest(floorNumber);
    this->elevator->addRequest(floorNumber);
}
