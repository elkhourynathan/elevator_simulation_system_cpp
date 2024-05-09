#include "Floor.h"
#include <QDebug>

Floor::Floor(ElevatorControlSystem* ecs, int floorNumber, QObject* parent) :  QObject(parent), floorNumber(floorNumber), ecs(ecs) {
    this->panel = new FloorPanel(this);
}

Floor::~Floor() {
    delete this->panel;
}

// Informs ECS of a floor pres
void Floor::inform(QString direction) {
    qDebug()<< "Passenger requests elevator on floor" << floorNumber << "to go" << direction;
    this->ecs->floorRequest(floorNumber, direction);
}

// Services the floor
void Floor::serviced() {
    qDebug()<<"Floor "<<floorNumber<<"serviced";
    close();
    this->panel->deactivate();
}

// Open floor doors
void Floor::open() {
     qDebug() << "Floor" << floorNumber << "doors are opening.";
}

// Close floor doors
void Floor::close() {
    qDebug() << "Floor " << floorNumber << " doors are closing";
}

// Takes in a Passenger* p and adds p to the floor
void Floor::addPassenger(Passenger* p){
    p->setFloor(this);
    this->passengers.append(p);
}

// Removes a Passenger* p from floor
Passenger* Floor::removePassenger(Passenger* p){
    // Check if the passenger is in the list
    int index = this->passengers.indexOf(p);
    if(index != -1){
        // Remove the passenger from the list
        this->passengers.removeAt(index);
        return p;
    }
    return nullptr;
}

FloorPanel* Floor::getPanel() const {
    return this->panel;
}
