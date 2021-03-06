#include <iostream>
#include "Worker.h"
#include "constants.h"

WArgs::WArgs(int waiting, Uint32 nmutex, Uint32 nbus, Uint32 nboarded) {
    this->waiting = waiting;
    this->mutex = SDL_CreateSemaphore(nmutex);
    this->bus = SDL_CreateSemaphore(nbus);
    this->boarded = SDL_CreateSemaphore(nboarded);
    this->cout = SDL_CreateSemaphore(1);
}

WArgs::~WArgs() {
    SDL_DestroySemaphore(mutex);
    SDL_DestroySemaphore(bus);
    SDL_DestroySemaphore(boarded);
}

Worker::Worker(int id, Street *street, WArgs *args) {
    this->id = id;
    this->street = street;
    this->args = args;
}

void Worker::log(string message) {
    SDL_SemWait(args->cout);

    cout << "[" << id << "] " << message << endl;

    SDL_SemPost(args->cout);
}

int Worker::worker(void *arg) {
    Worker *worker = (Worker *) arg;

    delay(WORKER_SETUP_DELAY);

    while (1) {
        worker->work();
    }

    return 0;
}

void Worker::delay(Uint32 time) {
    double r = 2 * ((rand() % WORKER_RAND_RANGE) - WORKER_RAND_RANGE);
    double v = 1 + r * WORKER_RAND_VARIATION / WORKER_RAND_RANGE;
    Uint32 t = (Uint32) (time * v);
    SDL_Delay(t);
}