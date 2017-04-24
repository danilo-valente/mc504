#include <iostream>
#include "Bus.h"
#include "constants.h"

using namespace std;

Bus::Bus(int id, Street *street, WArgs *args) : Worker(id, street, args) {
    aboard = 0;
    street->addBus(&shape);
}

void Bus::arrive() {
    aboard = 0;

    update(BUS_ARRIVING);

    log("Bus is arriving");

    SDL_Delay(BUS_ARRIVAL_DELAY);

    SDL_SemWait(args->mutex);

    log("Bus just arrived");
}

void Bus::wait() {
    update(BUS_WAITING);

    int n = min(args->waiting, BUS_SEATS);
    for (int i = 0; i < n; i++) {
        SDL_SemPost(args->bus);
        SDL_SemWait(args->boarded);
        aboard++;
    }

    args->waiting = max(args->waiting - BUS_SEATS, 0);

    SDL_SemPost(args->mutex);
}

void Bus::depart() {
    update(BUS_DEPARTING);

    log("Bus is departing with " + to_string(aboard) + " riders aboard");

    SDL_Delay(BUS_DEPARTURE_DELAY);

    update(BUS_AWAY);

    log("Bus just departed");

    SDL_Delay(BUS_RIDE_DELAY);
}

int Bus::work() {
    arrive();

    wait();

    depart();

    return 0;
}

void Bus::update(BusStatus status) {
    shape.status = status;
    street->draw();
}