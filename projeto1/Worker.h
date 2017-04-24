#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <SDL.h>
#include "Street.h"

using namespace std;

class WArgs {
public:
    int waiting;
    SDL_sem *mutex;
    SDL_sem *bus;
    SDL_sem *boarded;
    SDL_sem *cout;

    WArgs(int waiting, Uint32 nmutex, Uint32 nbus, Uint32 nboarded);
    ~WArgs();
};

class Worker {
public:
    Worker(int id, Street *street, WArgs *args);

    void log(string message);
    virtual int work() = 0;

    static int worker(void *worker);

protected:
    int id;
    Street *street;
    WArgs *args;

    static void delay(Uint32 time);
};

#endif
