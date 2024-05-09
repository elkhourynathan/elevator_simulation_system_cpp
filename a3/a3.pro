QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Elevator.cpp \
    ElevatorControlSystem.cpp \
    ElevatorPanel.cpp \
    ElevatorDoor.cpp \
    Floor.cpp \
    FloorPanel.cpp \
    FloorSensor.cpp \
    Passenger.cpp \
    Request.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    Elevator.h \
    ElevatorControlSystem.h \
    ElevatorDoor.h \
    ElevatorPanel.h \
    Floor.h \
    FloorPanel.h \
    FloorSensor.h \
    Passenger.h \
    Request.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
