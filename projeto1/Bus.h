#ifndef BUS_H
#define BUS_H

#include <SDL.h>

#include "Worker.h"

class Bus : public Worker {
public:
    int aboard;

    Bus(int id, SDL_Renderer *renderer, WArgs *args);

    void arrive();
    void wait();
    void depart();
    int work();
};

#endif
