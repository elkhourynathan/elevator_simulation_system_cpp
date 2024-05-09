#include "ElevatorControlSystem.h"


// Creates ECS with any number of elevators or floors
ElevatorControlSystem::ElevatorControlSystem(int numElevators, int numFloors, QObject* parent) : QObject(parent), numElevators(numElevators), numFloors(numFloors), safeFloor(1){
    qDebug()<<"Creating ECS with " << numElevators << "elevators" << " and " << numFloors<< " floors";
}

ElevatorControlSystem::~ElevatorControlSystem(){

}

// Processes the first request in the queue, selecting an elevator to handle the request based on proximity and direction.
void ElevatorControlSystem::makeDecision(){
    if(this->requestsQueue.isEmpty()){
        return;
    }

    Request* request = this->requestsQueue.first();
    int requestedFloor = request->floor;
    QString requestDirection = request->direction;
    Elevator* chosenElevator = nullptr;
    int minDistance = std::numeric_limits<int>::max();

    // First, try to find an elevator that is moving towards the requested floor in the same direction
    for (Elevator* elevator : this->elevators) {
        if (!elevator->requests.isEmpty() && elevator->direction == requestDirection) {
            int distance = qAbs(elevator->getCurrentFloor() - requestedFloor);
            // Prioritize elevators moving towards the requested floor
            if (distance < minDistance && ((elevator->direction == "up" && elevator->getCurrentFloor() <= requestedFloor) || (elevator->direction == "down" && elevator->getCurrentFloor() >= requestedFloor))) {
                chosenElevator = elevator;
                minDistance = distance;
            }
        }
    }

    // If no moving elevator is suitable, try to find an idle elevator
    if (!chosenElevator) {
        for (Elevator* elevator : this->elevators) {
            if (elevator->requests.isEmpty()) {
                int distance = qAbs(elevator->getCurrentFloor() - requestedFloor);
                if (distance < minDistance) {
                    chosenElevator = elevator;
                    minDistance = distance;
                }
            }
        }
    }

    // If no idle elevator is found, choose the closest one
    if (!chosenElevator) {
        for (Elevator* elevator : this->elevators) {
            int distance = qAbs(elevator->getCurrentFloor() - requestedFloor);
            if (distance < minDistance) {
                chosenElevator = elevator;
                minDistance = distance;
            }
        }
    }

    if (chosenElevator) {
        qDebug() << "ECS has assigned request for floor" << requestedFloor << "to elevator" << chosenElevator->getElevatorNum();
        chosenElevator->addRequest(requestedFloor);
        this->requestsQueue.pop_front(); // Remove the processed request
    }
}


// Method to add a new floor request to the queue and triggers the decision
void ElevatorControlSystem::floorRequest(int floorNumber, QString direction){
    qDebug()<< "ECS processing request for floor " << floorNumber << " to go" << direction;
    Request* request = new Request(floorNumber, direction);
    this->requestsQueue.push_front(request);
    makeDecision();
}

// Method to indicate elevator is ready to move
void ElevatorControlSystem::readyToMove(Elevator *elevator){}


// MEthod to handle elevator arriving
void ElevatorControlSystem::arrived(Elevator *elevator, int floorNum){

    // Find the corresponding floor object
    Floor* floorPtr = findFloor(floorNum);
    floorPtr->open();
    if (floorPtr != nullptr){

        for(Passenger* p : elevator->passengers){
            if(p->getDest() != -1 and p->getDest() == elevator->getCurrentFloor()){
                p->setDest(-1);
                elevator->disembark(p);
                floorPtr->addPassenger(p);
            }
        }
        for(Passenger* p : floorPtr->passengers){
            if(p->getDest() != -1 and p->getDest() == floorPtr->getFloorNumber()){
                p->setDest(-1);
                floorPtr->passengers.removeOne(p);
                elevator->embark(p);
            }
        }
    }
    depart(elevator, floorNum);
}

// Helper method to find a floor by its number
Floor* ElevatorControlSystem::findFloor(int floorNum) {
    for (Floor* floor : this->floors) {
        if(floor->getFloorNumber() == floorNum) {
            return floor;
        }
    }
    return nullptr;
}

// Method to handle floor being serviced
void ElevatorControlSystem::depart(Elevator *elevator, int floorNum){
    for(Floor* f : this->floors){
        if(f->getFloorNumber() == floorNum){
            f->serviced();
        }
    }
}

// Method to handle ECS fire alert, notifies all elevators
void ElevatorControlSystem::fire(){
    for (Elevator* elevator : this->elevators){
        elevator->fire("Fire alert");
        elevator->moveToSafeFloor(this->safeFloor);
    }
}

// Method to handle ECS power outage alert, notifies all elevators
void ElevatorControlSystem::powerOutage(){
    for (Elevator* elevator : this->elevators){
        elevator->powerOutage("Power Outage alert");
        elevator->moveToSafeFloor(this->safeFloor);
    }
}

// Method to connect to building safety services randomly return a true or false value
bool ElevatorControlSystem::connectBuildingSafetyService(){
    return QRandomGenerator::global()->generate() % 2 == 0;
}

// Method to dial emergency services
void ElevatorControlSystem::dialEmergencyServices(){
    qDebug()<<"Dialing emergency services";
}

// Method to handle a help call from Elevator* e
void ElevatorControlSystem::help(Elevator* e){
    if (connectBuildingSafetyService()) {
            qDebug() << "Building safety service connected successfully.";
            if(e->passengers.first()->speak()){
                e->connectCaller();
            } else{
                this->dialEmergencyServices();
            }
        } else {
            qDebug() << "Failed to connect to building safety service.";
            this->dialEmergencyServices();
        }
}


// Method to add elevator to ECS
void ElevatorControlSystem::addElevator(Elevator *elevator){
    this->elevators.push_back(elevator);
}

// Method to add floor to ECS
void ElevatorControlSystem::addFloor(Floor *floor){
    this->floors.push_back(floor);
}
