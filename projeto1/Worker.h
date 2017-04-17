#ifndef WORKER_H
#define WORKER_H

#include <SDL.h>

#include "LTexture.h"
#include "Dot.h"

class Worker {
public:
    Worker(int id, Dot *dots, int n, int delay, SDL_Renderer *renderer, SDL_sem *dataLock);

    static int work(void *worker);

private:
    int id;
    Dot *dots;
    int n;
    int delay;
    SDL_Renderer *renderer;
    SDL_sem *dataLock;
};

#endif
