#include <iostream>
#include "Rider.h"
#include "constants.h"

using namespace std;

Rider::Rider(int id, Street *street, WArgs *args) : Worker(id, street, args) {
    street->addRider(&shape);
}

void Rider::arrive() {
    update(RIDER_ARRIVING);

    delay(RIDER_ARRIVAL_DELAY);

    SDL_SemWait(args->mutex);

    args->waiting++;

    update(RIDER_WAITING);

    SDL_SemPost(args->mutex);
}

void Rider::board() {
    SDL_SemWait(args->bus);

    update(RIDER_BOARDING);

    delay(RIDER_BOARDING_DELAY);

    update(RIDER_AWAY);

    SDL_SemPost(args->boarded);

    delay(RIDER_RIDE_DELAY);
}

int Rider::work() {
    arrive();

    board();

    return 0;
}

void Rider::update(RiderStatus status) {
    shape.status = status;
    street->draw();

    switch (status) {
        case RIDER_ARRIVING:
            log("Rider is arriving");
            break;
        case RIDER_WAITING:
            log("Rider just arrived");
            log("There are " + to_string(args->waiting) + " riders waiting");
            break;
        case RIDER_BOARDING:
            log("Rider is boarding");
            break;
        case RIDER_AWAY:
            log("Rider just boarded");
            break;
    }
}