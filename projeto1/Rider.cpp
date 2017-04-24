#include <iostream>
#include "Rider.h"
#include "constants.h"

using namespace std;

Rider::Rider(int id, SDL_Renderer *renderer, WArgs *args) : Worker(id, renderer, args) {
    status = RIDER_AWAY;
}

void Rider::arrive() {
    status = RIDER_ARRIVING;

    log("Rider is arriving");

    SDL_Delay(RIDER_ARRIVAL_DELAY);

    SDL_SemWait(args->mutex);

    args->waiting++;

    status = RIDER_WAITING;

    log("Rider just arrived");

    SDL_SemPost(args->mutex);
}

void Rider::board() {
    SDL_SemWait(args->bus);

    status = RIDER_BOARDING;

    log("Rider is boarding");

    SDL_Delay(RIDER_BOARDING_DELAY);

    log("Rider just boarded");

    status = RIDER_AWAY;

    SDL_SemPost(args->boarded);
}

int Rider::work() {
    arrive();
    board();

    return 0;
}
