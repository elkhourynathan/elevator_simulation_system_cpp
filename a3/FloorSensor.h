// FloorSensor.h
#ifndef FLOOR_SENSOR_H
#define FLOOR_SENSOR_H

class Elevator;

class FloorSensor {
private:
    Elevator *elevator;
public:
    FloorSensor(Elevator* elevator);
    ~FloorSensor();

    void detect(int floorNumber);
};

#endif // FLOOR_SENSOR_H
