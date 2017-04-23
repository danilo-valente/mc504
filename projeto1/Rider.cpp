#include <iostream>
#include "Rider.h"
#include "constants.h"

using namespace std;

Rider::Rider(int id, SDL_Renderer *renderer, WArgs *args) : Worker(id, renderer, args) {}

void Rider::arrive() {
    log("Rider is arriving");

    SDL_Delay(RIDER_ARRIVAL_DELAY);

    SDL_SemWait(args->mutex);

    args->waiting++;

    log("Rider just arrived");
    log("There are " + to_string(args->waiting) + " riders waiting");

    SDL_SemPost(args->mutex);
}

void Rider::board() {
    SDL_SemWait(args->bus);

    log("Rider is boarding");

    SDL_Delay(RIDER_BOARDING_DELAY);

    log("Rider just boarded");

    SDL_SemPost(args->boarded);
}

int Rider::work() {
    arrive();
    board();

    return 0;
}
