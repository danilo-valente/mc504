#ifndef RIDER_H
#define RIDER_H

#include <SDL.h>

#include "Worker.h"

class Rider : public Worker {
public:
    Rider(int id, SDL_Renderer *renderer, WArgs *args);

    void arrive();
    void board();
    int work();
};

#endif
