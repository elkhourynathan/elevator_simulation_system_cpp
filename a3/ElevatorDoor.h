// ElevatorDoor.h
#ifndef ELEVATOR_DOOR_H
#define ELEVATOR_DOOR_H

class Elevator;

class ElevatorDoor {
    friend class Elevator;
private:
    bool opened;
    bool obstructed;
    int repeatedObstruction;
    Elevator *elevator;

public:
    ElevatorDoor(Elevator* elevator);
    ~ElevatorDoor();

    void openDoor();
    bool closeDoor();
    bool checkObstruction();

    void setObstruction(bool obstructed);

};

#endif // ELEVATOR_DOOR_H
