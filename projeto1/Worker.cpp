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

Worker::Worker(int id, SDL_Renderer *renderer, WArgs *args) {
    this->id = id;
    this->renderer = renderer;
    this->args = args;
}

void Worker::log(string message) {
    SDL_SemWait(args->cout);

    cout << "[" << id << "] " << message << endl;

    SDL_SemPost(args->cout);
}

//int Worker::work() {
//    printf("[#%d] starting...\n", this->id);
//
//    //Pre thread random seeding
//    srand(SDL_GetTicks());
//
//    //Wait randomly
//    SDL_Delay(16 + rand() % 32);
//
//    //Lock
//    SDL_SemWait(this->dataLock);
//
//    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//    SDL_RenderClear(this->renderer);
//
//    printf("[#%d] render\n", this->id);
//    for (int j = 0; j < this->n; j++) {
//        this->dots[j].setColor(j == this->id ? COLOR_GREEN : COLOR_RED);
//        this->dots[j].render();
//    }
//
//    SDL_RenderPresent(this->renderer);
//
//    //Wait
//    SDL_Delay(DEFAULT_DELAY);
//
//    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//    SDL_RenderClear(this->renderer);
//
//    printf("[#%d] hide\n", this->id);
//    for (int j = 0; j < this->n; j++) {
//        this->dots[j].setColor(COLOR_RED);
//        this->dots[j].render();
//    }
//
//    SDL_RenderPresent(this->renderer);
//
//    //Unlock
//    SDL_SemPost(this->dataLock);
//
//    //Wait randomly
//    SDL_Delay(16 + rand() % 640);
//
//    printf("[#%d] finished!\n", this->id);
//
//    return 0;
//}

int Worker::worker(void *arg) {
    Worker *worker = (Worker *) arg;

    SDL_Delay(WORKER_SETUP_DELAY);

    while (1) {
        worker->work();
    }

    return 0;
}