// ElevatorControlSystem.h
#ifndef ELEVATOR_CONTROL_SYSTEM_H
#define ELEVATOR_CONTROL_SYSTEM_H

#include <QRandomGenerator>
#include <QVector>
#include <QString>
#include <QDebug>
#include "Request.h"
#include "Elevator.h"

class Floor;
class Elevator;


class ElevatorControlSystem : public QObject{
    Q_OBJECT
private:
    int numElevators;
    int numFloors;
    int safeFloor;
    QVector<Request*> requestsQueue;
    QVector<Elevator*> elevators;
    QVector<Floor*> floors;

    void makeDecision();

public:
    ElevatorControlSystem(int numElevators, int numFloors, QObject* parent=nullptr);
    ~ElevatorControlSystem();

    void floorRequest(int floorNumber, QString direction);
    void readyToMove(Elevator* elevator);
    void arrived(Elevator* elevator, int floorNum);
    void depart(Elevator* elevator, int floorNum);

    void fire();
    void powerOutage();

    bool connectBuildingSafetyService();
    void dialEmergencyServices();
    void help(Elevator* e);

    void addElevator(Elevator* elevator);
    void addFloor(Floor* floor);

    Floor* findFloor(int floorNum);


};

#endif // ELEVATOR_CONTROL_SYSTEM_H
