#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>

#include "ElevatorControlSystem.h"
#include "Elevator.h"
#include "ElevatorDoor.h"
#include "ElevatorPanel.h"

#include "Floor.h"
#include "FloorPanel.h"
#include "FloorSensor.h"

#include "Passenger.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitializeSystem();

private:
    Ui::MainWindow *ui;
    ElevatorControlSystem* ecs;
    QVector<Elevator*> elevators;
    QVector<Floor*> floors;
    QVector<Passenger*> passengers;

private slots:
    void ecsFireAlert();
    void ecsPowerOutageAlert();
    void scenarioDefault();
    void scenarioSuccess1();
    void scenarioSuccess2();
    void scenarioOverload();
    void scenarioObstruction();
    void passengerPressedHelp();
    void passengerAddStop(int pressedFloor);
    void requestFloorUp();
    void requestFloorDown();
    void elevatorHelpPressed();
    void onElevatorArrived(int elevatorNumber, int floorNumber);
};
#endif // MAINWINDOW_H
