#ifndef RIDER_H
#define RIDER_H

#include <SDL.h>

#include "Worker.h"
#include "Street.h"
#include "RiderStatus.h"
#include "RiderShape.h"

class Rider : public Worker {
public:
    RiderShape shape;

    Rider(int id, Street *street, WArgs *args);

protected:
    int work();

private:
    void arrive();
    void board();
    void update(RiderStatus status);
};

#endif
