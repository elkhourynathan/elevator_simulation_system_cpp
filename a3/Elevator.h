// Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <string>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include "Request.h"
#include "ElevatorPanel.h"
#include "ElevatorDoor.h"
#include "FloorSensor.h"
#include "Passenger.h"
#include "Floor.h"

class ElevatorControlSystem;
class ElevatorPanel;

class Elevator : public QObject{
    Q_OBJECT

    friend class ElevatorControlSystem;

    private:
        int elevatorNum;
        int currentFloor;
        int weightCapacity;
        bool moving;
        QString direction;
        ElevatorControlSystem *ecs;
        ElevatorPanel *panel;
        ElevatorDoor *door;
        FloorSensor *sensor;
        QVector<Request*> requests;
        QVector<Passenger*> passengers;
        QTimer* timer;

    private slots:
        void move();

    signals:
        void arrived(int elevatorNumber, int floorNumber);

    public:
        Elevator(ElevatorControlSystem* ecs, int elevatorNum, QObject* parent = nullptr);
        ~Elevator();

        void addRequest(int floorNumber);
        void start();
        void stop(int floorNumber);
        void embark(Passenger* p);
        Passenger* disembark(Passenger* p);

        void openDoor();
        bool closeDoor();

        void help();
        bool overloaded();
        void fire(QString message);
        void powerOutage(QString message);
        void moveToSafeFloor(int floorNumber);

        void updateDisplay(QString message);
        void playAudio(QString message);
        void updateFloor(int floorNumber);
        void ring();
        void connectCaller();

        int getCurrentFloor() const;
        bool isMoving() const;
        int getElevatorNum() const;
        int getWeightCapacity() const;
        QVector<Passenger*> getPassengerList() const;
        void setWeightCapacity(int newCapacity);
        ElevatorPanel* getPanel() const;
        void setObstruction();
        void handleObstruction();

        void setFloor(int floor);


};

#endif // ELEVATOR_H
