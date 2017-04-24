#ifndef RIDER_H
#define RIDER_H

#include <SDL.h>

#include "Worker.h"
#include "RiderStatus.h"
#include "RiderShape.h"

class Rider : public Worker {
public:
    RiderShape shape;

    Rider(int id, Street *street, WArgs *args);
private:
    void arrive();
    void board();
    int work();
    void update(RiderStatus status);
};

#endif
