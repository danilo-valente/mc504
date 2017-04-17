#include "Worker.h"

Worker::Worker(int id, Dot *dots, int n, int delay, SDL_Renderer *renderer, SDL_sem *dataLock) {
    this->id = id;
    this->dots = dots;
    this->n = n;
    this->delay = delay;
    this->renderer = renderer;
    this->dataLock = dataLock;
}

int Worker::work(void *arg) {
    Worker *worker = (Worker *) arg;
    printf("[#%d] starting...\n", worker->id);

    //Pre thread random seeding
    srand(SDL_GetTicks());

    //Work 5 times
    for (int i = 0; i < 5; ++i) {
        //Wait randomly
        SDL_Delay(16 + rand() % 32);

        //Lock
        SDL_SemWait(worker->dataLock);

        SDL_SetRenderDrawColor(worker->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(worker->renderer);

        printf("[#%d] render\n", worker->id);
        worker->dots[worker->id].render();

        SDL_RenderPresent(worker->renderer);

        //Wait
        SDL_Delay(worker->delay);

        SDL_SetRenderDrawColor(worker->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(worker->renderer);

        printf("[#%d] hide\n", worker->id);

        SDL_RenderPresent(worker->renderer);

        //Unlock
        SDL_SemPost(worker->dataLock);

        //Wait randomly
        SDL_Delay(16 + rand() % 640);
    }

    printf("[#%d] finished!\n", worker->id);

    return 0;
}