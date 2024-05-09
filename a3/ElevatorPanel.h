// ElevatorPanel.h
#ifndef ELEVATOR_PANEL_H
#define ELEVATOR_PANEL_H

#include <QString>
#include "Passenger.h"
#include "Elevator.h"

class Elevator;
class Passenger;

class ElevatorPanel {
private:
    int floor;
    QString visualMessage;
    Elevator *elevator;


public:
    ElevatorPanel(Elevator* elevator);
    ~ElevatorPanel();

    void help();
    void manualOpen();
    void manualClose();
    void addStop(Passenger* p, int floorNumber);


};

#endif // ELEVATOR_PANEL_H
