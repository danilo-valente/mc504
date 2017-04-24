#include <iostream>
#include "Rider.h"
#include "constants.h"

using namespace std;

Rider::Rider(int id, Street *street, WArgs *args) : Worker(id, street, args) {
    street->addRider(&shape);
}

void Rider::arrive() {
    update(RIDER_ARRIVING);

    log("Rider is arriving");

    SDL_Delay(RIDER_ARRIVAL_DELAY);

    SDL_SemWait(args->mutex);

    args->waiting++;

    update(RIDER_WAITING);

    log("Rider just arrived");

    SDL_SemPost(args->mutex);
}

void Rider::board() {
    SDL_SemWait(args->bus);

    update(RIDER_BOARDING);

    log("Rider is boarding");

    SDL_Delay(RIDER_BOARDING_DELAY);

    log("Rider just boarded");

    update(RIDER_AWAY);

    SDL_SemPost(args->boarded);
}

int Rider::work() {
    arrive();

    board();

    return 0;
}

void Rider::update(RiderStatus status) {
    shape.status = status;
    street->draw();
}