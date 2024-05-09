#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Create ECS
    ecs = new ElevatorControlSystem(3, 7, this);

    // Create the floors and elevators
    for (int i = 0; i < 7; ++i) {
        Floor* floor = new Floor(ecs, i + 1);
        floors.push_back(floor);
        ecs->addFloor(floor);
    }

    for (int i = 0; i < 3; ++i) {
        Elevator* elevator = new Elevator(ecs, i + 1, this);
        elevators.push_back(elevator);
        ecs->addElevator(elevator);

        // Connect signals from each elevator for real-time updates
        connect(elevator, &Elevator::arrived, this, &MainWindow::onElevatorArrived);
    }

    Passenger* p1 = new Passenger(1);
    Passenger* p2 = new Passenger(2);
    Passenger* p3 = new Passenger(3);
    this->passengers.append(p1);
    this->passengers.append(p2);
    this->passengers.append(p3);


    // Connect UI signals
    connect(ui->ecsFire, &QPushButton::released, this, &MainWindow::ecsFireAlert);
    connect(ui->ecsPowerOutage, &QPushButton::released, this, &MainWindow::ecsPowerOutageAlert);
    connect(ui->scenarioOverload, &QPushButton::released, this, &MainWindow::scenarioOverload);
    connect(ui->scenarioObstruction, &QPushButton::released, this, &MainWindow::scenarioObstruction);
    connect(ui->floorPanelUpButton, &QPushButton::released, this, &MainWindow::requestFloorUp);
    connect(ui->floorPanelDown, &QPushButton::released, this, &MainWindow::requestFloorDown);
    connect(ui->scenarioSucess, &QPushButton::released, this, &MainWindow::scenarioSuccess1);
    connect(ui->scenarioSuccess2, &QPushButton::released, this, &MainWindow::scenarioSuccess2);
    connect(ui->scenarioDefault, &QPushButton::released, this, &MainWindow::scenarioDefault);

    connect(ui->elevatorDest1, &QPushButton::released, this, [this]() { passengerAddStop(1); });
    connect(ui->elevatorDest2, &QPushButton::released, this, [this]() { passengerAddStop(2); });
    connect(ui->elevatorDest3, &QPushButton::released, this, [this]() { passengerAddStop(3); });
    connect(ui->elevatorDest4, &QPushButton::released, this, [this]() { passengerAddStop(4); });
    connect(ui->elevatorDest5, &QPushButton::released, this, [this]() { passengerAddStop(5); });
    connect(ui->elevatorDest6, &QPushButton::released, this, [this]() { passengerAddStop(6); });
    connect(ui->elevatorDest7, &QPushButton::released, this, [this]() { passengerAddStop(7); });
    connect(ui->elevatorHelp, &QPushButton::released, this, &MainWindow::elevatorHelpPressed);





}


MainWindow::~MainWindow()
{
    delete ui;

    for (Elevator* elevator : this->elevators){
        delete elevator;
    }

    for(Floor* floor : this->floors){
        delete floor;
    }

    for (Passenger* passenger : this->passengers){
        delete passenger;
    }
}

// Defaults conditions
void MainWindow::scenarioDefault(){
    qDebug()<<"------------- ESTABLISHING PRECONDITIONS -------------";
    qDebug()<<"Resetting elevator positions to 1";
    for (Passenger* p : this->passengers){
        p->setDest(-1);
        p->setElevator(nullptr);
        p->setFloor(nullptr);
    }

    for (Elevator* e : this->elevators){
        e->setFloor(1);
    }
}

// Simulation for scenario 1
void MainWindow::scenarioSuccess1(){
    qDebug()<<"------------- ESTABLISHING PRECONDITIONS -------------";
    qDebug()<<"Moving elevator 3 to floor 7";
    // Set up preconditions
    elevators[2]->setFloor(7);
}

// Simulation for scenario 2
void MainWindow::scenarioSuccess2(){
    qDebug()<<"------------- ESTABLISHING PRECONDITIONS -------------";
    qDebug()<<"Moving elevator 3 to floor 3";
    // Set up preconditions
    elevators[2]->setFloor(3);
    elevators.move(2,1);
}

// Simulation scenario for a fire alert
void MainWindow::ecsFireAlert(){
    ecs->fire();
}

// Simulation scenario for a power outage
void MainWindow::ecsPowerOutageAlert(){
    ecs->powerOutage();
}

// Test scenario for a overload
void MainWindow::scenarioOverload(){
    qDebug()<<"------------- RUNNING SCENARIO OVERLOAD -------------";
    Elevator* testElevator = this->elevators[0];
    testElevator->setWeightCapacity(199);
    testElevator->embark(passengers[1]);
    QThread::sleep(1);
    testElevator->embark(passengers[0]);
    QThread::sleep(1);

    testElevator->disembark(passengers[0]);

    testElevator->closeDoor();
    testElevator->start();

    // Reset elevator weight to default
    testElevator->setWeightCapacity(200);


}

void MainWindow::scenarioObstruction(){
    qDebug()<<"------------- RUNNING SCENARIO OBSTRUCTION -------------";
    Elevator* testElevator = this->elevators[0];
    Passenger* testPassenger = this->passengers[0];
    // precondition
    testElevator->setObstruction();
    testElevator->embark(testPassenger);
    QThread::sleep(1);
    testElevator->closeDoor();
    QThread::sleep(1);
    testElevator->closeDoor();
    QThread::sleep(1);
    testElevator->closeDoor();

    QThread::sleep(1);
    testPassenger->handleObstruction();
    testElevator->closeDoor();
    testElevator->start();


}

void MainWindow::passengerPressedHelp(){}

// Adds passenger stop
void MainWindow::passengerAddStop(int pressedFloor){
    int passengerID = ui->passengerNumberSelector->currentText().toInt();
    int targetElevator = ui->elevatorSelector->currentText().toInt();

    Elevator* desiredElevator = nullptr;
    Passenger* desiredPassenger = nullptr;

    // find desired elevator
    for (Elevator* elevator : this->elevators){
        if(elevator->getElevatorNum() == targetElevator){
            desiredElevator = elevator;
            break;
        }
    }

    // Find desired passenger
    for (Passenger* passenger : this->passengers){
        if(passenger->getID() == passengerID){
            desiredPassenger = passenger;
            break;
        }
    }

    // call if found
    QVector<Passenger*> passengersInElevator = desiredElevator->getPassengerList();
    bool found = passengersInElevator.contains(desiredPassenger);
    if(!found){return;}

    desiredPassenger->setDest(pressedFloor);
    desiredElevator->addRequest(pressedFloor);



}

// Handle a floor request
void MainWindow::requestFloorUp(){
    int passengerID = ui->passengerNumberSelector->currentText().toInt();
    int requestedFloor = ui->floorNumberSelector->currentText().toInt();
    Floor* desiredFloor = nullptr;
    Passenger* desiredPassenger = nullptr;

    // Find desired floor
    for (Floor* floor : this->floors){
        if(floor->getFloorNumber() == requestedFloor){
            desiredFloor = floor;
            break;
        }
    }

    // Find desired passenger
    for (Passenger* passenger : this->passengers){
        if(passenger->getID() == passengerID){
            desiredPassenger = passenger;
            break;
        }
    }

    desiredPassenger->setDest(desiredFloor->getFloorNumber());
    desiredFloor->addPassenger(desiredPassenger);
    desiredFloor->inform("up");
}


// Handle a floor request
void MainWindow::requestFloorDown(){
    int passengerID = ui->passengerNumberSelector->currentText().toInt();
    int requestedFloor = ui->floorNumberSelector->currentText().toInt();
    Floor* desiredFloor = nullptr;
    Passenger* desiredPassenger = nullptr;

    // Find desired floor
    for (Floor* floor : this->floors){
        if(floor->getFloorNumber() == requestedFloor){
            desiredFloor = floor;
            break;
        }
    }

    // Find desired passenger
    for (Passenger* passenger : this->passengers){
        if(passenger->getID() == passengerID){
            desiredPassenger = passenger;
            break;
        }
    }
    desiredPassenger->setDest(desiredFloor->getFloorNumber());
    desiredFloor->addPassenger(desiredPassenger);
    desiredFloor->inform("down");
}

// Elevator help button method
void MainWindow::elevatorHelpPressed(){
    int passengerID = ui->passengerNumberSelector->currentText().toInt();
    int targetElevator = ui->elevatorSelector->currentText().toInt();

    Elevator* desiredElevator = nullptr;
    Passenger* desiredPassenger = nullptr;

    // Find desired elevator
    for (Elevator* elevator : this->elevators){
        if(elevator->getElevatorNum() == targetElevator){
            desiredElevator = elevator;
            break;
        }
    }

    // Find desired passenger
    for (Passenger* passenger : this->passengers){
        if(passenger->getID() == passengerID){
            desiredPassenger = passenger;
            break;
        }
    }

    QVector<Passenger*> passengersInElevator = desiredElevator->getPassengerList();
    bool found = passengersInElevator.contains(desiredPassenger);
    if(!found){return;}

    desiredPassenger->getElevator()->getPanel()->help();
}

// Notify on elevator arrival
void MainWindow::onElevatorArrived(int elevatorNumber, int floorNumber){
    qDebug() << "Elevator" << elevatorNumber<<" arrived at floor " << floorNumber;


}
