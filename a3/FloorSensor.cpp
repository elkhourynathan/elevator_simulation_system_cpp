#include "FloorSensor.h"
#include "Elevator.h"

FloorSensor::FloorSensor(Elevator* elevator) : elevator(elevator) {
}

FloorSensor::~FloorSensor() {
}

// Detects floor sensor movements
void FloorSensor::detect(int floorNumber) {
    this->elevator->updateFloor(floorNumber);
}
