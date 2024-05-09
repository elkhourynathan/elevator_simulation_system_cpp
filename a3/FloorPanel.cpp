#include "FloorPanel.h"
#include "Floor.h"


FloorPanel::FloorPanel(Floor* floor): upButtonPressed(false), downButtonPressed(false), floor(floor){}

FloorPanel::~FloorPanel(){}

// Method to handle floorpanel up and update passener
void FloorPanel::pressUp(Passenger* p){
    qDebug()<<"Floor "<<this->floor->getFloorNumber()<<" up button pressed";
    p->setDest(this->floor->getFloorNumber());
    this->upButtonPressed = true;
    this->floor->inform("up");
}

// Method to handle floorpanel down and update passener
void FloorPanel::pressDown(Passenger* p){
    qDebug()<<"Floor "<<this->floor->getFloorNumber()<<" up button pressed";
    p->setDest(this->floor->getFloorNumber());
    this->downButtonPressed = true;
    floor->inform("down");
}

// Handles deactivation of floor buttons
void FloorPanel::deactivate(){
    this->upButtonPressed = false;
    this->downButtonPressed = false;
}
