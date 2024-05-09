// Request.h
#ifndef REQUEST_H
#define REQUEST_H

#include <QString>

class Request {
public:
    int floor;
    QString direction;
    Request(int floor, QString direction);
    ~Request();
};

#endif // REQUEST_H
