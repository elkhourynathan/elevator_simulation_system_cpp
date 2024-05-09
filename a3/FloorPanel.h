// FloorPanel.h
#ifndef FLOOR_PANEL_H
#define FLOOR_PANEL_H

#include <QString>
#include "Passenger.h"

using namespace std;

class Floor;
class Passenger;

class FloorPanel {
private:
    bool upButtonPressed;
    bool downButtonPressed;
    Floor* floor;


public:
    FloorPanel(Floor* floor);
    ~FloorPanel();

    void pressUp(Passenger* p);
    void pressDown(Passenger* p);
    void deactivate();

};

#endif // FLOOR_PANEL_H
