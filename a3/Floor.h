// Floor.h
#ifndef FLOOR_H
#define FLOOR_H

#include <QString>
#include <QDebug>
#include "FloorPanel.h"
#include "ElevatorControlSystem.h"

using namespace std;

class ElevatorControlSystem;
class Passenger;
class FloorPanel;

class Floor : public QObject {
    Q_OBJECT

    friend class ElevatorControlSystem;
private:
    int floorNumber;
    FloorPanel *panel;
    ElevatorControlSystem *ecs;
    QVector<Passenger*> passengers;

public:
    Floor(ElevatorControlSystem* ecs, int floorNumber, QObject* parent = nullptr);
    ~Floor();

    void inform(QString direction);
    void serviced();
    void open();
    void close();

    void addPassenger(Passenger* p);
    Passenger* removePassenger(Passenger* p);

    int getFloorNumber() const {
        return this->floorNumber;
    }
    FloorPanel* getPanel() const;

};

#endif // FLOOR_H
