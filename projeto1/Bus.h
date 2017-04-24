#ifndef BUS_H
#define BUS_H

#include <SDL.h>

#include "Worker.h"

typedef enum {
    BUS_AWAY,
    BUS_ARRIVING,
    BUS_WAITING,
    BUS_DEPARTING,
} BusStatus;

class Bus : public Worker {
public:
    BusStatus status;
    int aboard;

    Bus(int id, SDL_Renderer *renderer, WArgs *args);

    void arrive();
    void wait();
    void depart();
    int work();
};

#endif
