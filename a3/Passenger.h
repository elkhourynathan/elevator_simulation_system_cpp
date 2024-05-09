// Passenger.h
#ifndef PASSENGER_H
#define PASSENGER_H

#include <QDebug>
#include <QRandomGenerator>
#include "Elevator.h"
#include "Floor.h"

class Elevator;
class Floor;

class Passenger {
private:
    int id;
    int currentFloor;
    int destinationFloor;
    int weight;
    Elevator* curElevator;
    Floor* curFloor;

public:
    Passenger(int id);
    ~Passenger();

    bool speak();
    void handleObstruction();
//    void embark(Elevator* elevator);
//    void disembark(Elevator* elevator);
    void pressHelp();

    int getID() const;
    int getWeight() const;
    int getDest() const;

    void setElevator(Elevator* e);
    void setFloor(Floor* f);
    void setDest(int n);
    Floor* getFloor() const;
    Elevator* getElevator() const;
};

#endif // PASSENGER_H
