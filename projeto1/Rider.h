#ifndef RIDER_H
#define RIDER_H

#include <SDL.h>

#include "Worker.h"

typedef enum {
    RIDER_AWAY,
    RIDER_ARRIVING,
    RIDER_WAITING,
    RIDER_BOARDING
} RiderStatus;

class Rider : public Worker {
public:
    RiderStatus status;

    Rider(int id, SDL_Renderer *renderer, WArgs *args);

    void arrive();
    void board();
    int work();
};

#endif
