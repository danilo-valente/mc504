#ifndef BUS_H
#define BUS_H

#include <SDL.h>

#include "Worker.h"
#include "Street.h"
#include "BusStatus.h"
#include "BusShape.h"

class Bus : public Worker {
public:
    BusShape shape;
    int aboard;

    Bus(int id, Street *street, WArgs *args);

protected:
    int work();

private:
    void arrive();
    void wait();
    void depart();
    void update(BusStatus status);
};

#endif
