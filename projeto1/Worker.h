#ifndef WORKER_H
#define WORKER_H

#include <SDL.h>

#include "LTexture.h"

class Worker {
public:
    Worker(int *data, SDL_sem *dataLock, char *name);

    static int work(void *worker);

private:
    int *data;
    SDL_sem *dataLock;
    char *name;
};

#endif
