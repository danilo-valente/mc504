#include <iostream>
#include "Rider.h"
#include "constants.h"

using namespace std;

Rider::Rider(int id, SDL_Renderer *renderer, WArgs *args) : Worker(id, renderer, args) {}

void Rider::arrive() {
    log("Rider is arriving");

    SDL_Delay(RIDER_ARRIVAL_DELAY);

    args->waiting++;

    log("Rider just arrived");
    cout << "[" << id << "] " << "There are " << args->waiting << " riders waiting" << endl;
}

void Rider::board() {
    log("Rider is boarding");

    SDL_Delay(RIDER_BOARDING_DELAY);

    log("Rider just boarded");
}

int Rider::work() {
    SDL_SemWait(args->mutex);

    arrive();

    SDL_SemPost(args->mutex);

    SDL_SemWait(args->bus);

    board();

    SDL_SemPost(args->boarded);

    return 0;
}
