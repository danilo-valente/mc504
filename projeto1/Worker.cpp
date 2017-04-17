#include "Worker.h"

Worker::Worker(int *data, SDL_sem *dataLock, char *name) {
    this->data = data;
    this->dataLock = dataLock;
    this->name = name;
}

int Worker::work(void *arg) {
    Worker *worker = (Worker *) arg;
    printf("%s starting...\n", worker->name);

    //Pre thread random seeding
    srand(SDL_GetTicks());

    //Work 5 times
    for (int i = 0; i < 5; ++i) {
        //Wait randomly
        SDL_Delay(16 + rand() % 32);

        //Lock
        SDL_SemWait(worker->dataLock);

        //Print pre work data
        printf("%s gets %d\n", worker->name, *worker->data);

        //Wait
        SDL_Delay(1000);

        //"Work"
        *worker->data = rand() % 256;

        //Print post work data
        printf("%s sets %d\n\n", worker->name, *worker->data);

        //Unlock
        SDL_SemPost(worker->dataLock);

        //Wait randomly
        SDL_Delay(16 + rand() % 640);
    }

    printf("%s finished!\n\n", worker->name);

    return 0;
}