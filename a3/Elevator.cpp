#include "Elevator.h"

Elevator::Elevator(ElevatorControlSystem* ecs, int elevatorNum, QObject* parent) :
    QObject(parent),
    elevatorNum(elevatorNum),
    currentFloor(1),
    weightCapacity(300),
    moving(false),
    direction("0"),
    ecs(ecs),
    panel(new ElevatorPanel(this)),
    door(new ElevatorDoor(this)),
    sensor(new FloorSensor(this)),
    timer(new QTimer())
{

    connect(timer, &QTimer::timeout, this, &Elevator::move);
    qDebug() << "Creating elevator " << elevatorNum;
}


Elevator::~Elevator(){
    delete this->panel;
    delete this->door;
    delete this->sensor;
    delete this->timer;
}


// Method to take in floornumber and add request to elevator
void Elevator::addRequest(int floorNumber){
    qDebug() << "Elevator " << this->elevatorNum << " received request for floor " << floorNumber;

    QString direction = floorNumber > currentFloor ? "up" : "down";
    this->requests.push_front(new Request(floorNumber, direction));
    if (!moving) {
        start();
    }
}


// Method to start elevator's movement cycle
void Elevator::start(){
    if (!moving && !requests.isEmpty()) {
        Request* nextRequest = requests.first();
        direction = nextRequest->floor > currentFloor ? "up" : "down";
        moving = true;
        timer->start(3000);
    }
}

// Method to handle elevator movement
void Elevator::move(){
    if (moving) {
        if(currentFloor != requests.first()->floor){
            int nextFloor = currentFloor + (direction == "up" ? 1 : -1);
            this->sensor->detect(nextFloor);
        }

        if (!requests.isEmpty() && currentFloor == requests.first()->floor) {
            stop(currentFloor);
        }
    }
}

// Method to stop the elevator's movement
void Elevator::stop(int floorNumber){
    moving = false;
    timer->stop();

    if (!requests.isEmpty()) {
        requests.pop_front(); // Current request fulfilled
    }

    // Disembark passengers upon arrival
    qDebug() << "Elevator " << elevatorNum << " has arrived at floor " << floorNumber;
    ecs->arrived(this, floorNumber);
    this->start();
}

// Method to take in Passenger* p and handle embarking
void Elevator::embark(Passenger* p){
    this->passengers.append(p);
    p->setElevator(this);
    qDebug()<<"Passenger "<<p->getID()<<" embarked elevator "<<this->elevatorNum;
    if(this->overloaded()){
        this->updateDisplay("overloaded");
        this->playAudio("overloaded");
    }
}

//Method to take in Passenger* p and handle disembarking
Passenger* Elevator::disembark(Passenger* p){
    int index = this->passengers.indexOf(p);
    p->setElevator(nullptr);
    if(index != -1){
        // Remove the passenger from the list
        this->passengers.removeAt(index);
        // Return the removed passenger
        qDebug()<<"Passenger "<<p->getID()<<" disembarked elevator "<<this->elevatorNum;
        return p;
    }
    return nullptr;
}

// Method to open elevator door
void Elevator::openDoor(){
    this->door->openDoor();
}


// method to close elevator door
bool Elevator::closeDoor(){
    if(!this->overloaded()){
        this->door->closeDoor();
        return true;
    } else{
        return false;
    }
}

// Method to sent help request
void Elevator::help(){
    this->ecs->help(this);
}


// Method to check if elevator is overloaded and return true or false
bool Elevator::overloaded(){
    int sumWeight = 0;
    // Sum weight
    for (Passenger* passenger : this->passengers){
        sumWeight += passenger->getWeight();
    }
    // Check against capacity
    if(sumWeight > this->weightCapacity){
        qDebug()<<"Overloaded elevator "<<elevatorNum;
        return true;
    }else {
        qDebug()<<"Not overloaded elevator "<<elevatorNum;
        return false;
    }
}

// Method to handle fire call
void Elevator::fire(QString message){
    qDebug()<<message<<" alert received on elevator "<<this->elevatorNum;
    this->updateDisplay(message);
    this->playAudio(message);
}

// Method to handle powerOutage call
void Elevator::powerOutage(QString message){
    qDebug()<<message<<" alert received on elevator "<<this->elevatorNum;
    this->updateDisplay(message);
}

// method to move to given safe floor
void Elevator::moveToSafeFloor(int floorNumber){
    if(!requests.isEmpty()){
        this->stop(this->currentFloor);
        this->requests.clear();
    }
    this->addRequest(floorNumber);
}

void Elevator::updateDisplay(QString message){
    qDebug()<<"display updated with: " << message<<" on elevator "<<this->elevatorNum;
}

void Elevator::playAudio(QString message){
    qDebug()<<"audio played: " << message<<" on elevator "<<this->elevatorNum;
}

void Elevator::updateFloor(int floorNumber){
    qDebug()<<"Elevator "<< this->elevatorNum << "moved to " << floorNumber;
    this->currentFloor = floorNumber;
}

void Elevator::ring(){
    qDebug()<<"bell ringed on elevator "<<this->elevatorNum;
}

void Elevator::connectCaller(){
    qDebug()<<"Passenger help received and caller connected";
}

int Elevator::getCurrentFloor() const {
    return this->currentFloor;
}

bool Elevator::isMoving() const{
    return this->moving;
}

int Elevator::getElevatorNum() const{
    return this->elevatorNum;
}

int Elevator::getWeightCapacity() const{
    return this->weightCapacity;
}

void Elevator::setWeightCapacity(int newCapacity){
    this->weightCapacity = newCapacity;
}

QVector<Passenger*> Elevator::getPassengerList() const {
    return passengers;
}

ElevatorPanel* Elevator::getPanel() const{
    return this->panel;
}

void Elevator::setFloor(int floor){
    this->currentFloor = floor;
}

void Elevator::setObstruction(){
    this->door->obstructed = true;
}

void Elevator::handleObstruction(){
    qDebug()<<"Handling obstruction on Elevator "<<this->elevatorNum;
    this->door->obstructed = false;
}
