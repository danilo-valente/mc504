#include <iostream>
#include "Bus.h"
#include "constants.h"

using namespace std;

Bus::Bus(int id, SDL_Renderer *renderer, WArgs *args) : Worker(id, renderer, args) {
    aboard = 0;
}

void Bus::arrive() {
    aboard = 0;

    log("Bus is arriving");

    SDL_Delay(BUS_ARRIVAL_DELAY);

    SDL_SemWait(args->mutex);

    log("Bus just arrived");
}

void Bus::wait() {
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
    log("Bus is departing with " + to_string(aboard) + " riders aboard");

    SDL_Delay(BUS_DEPARTURE_DELAY);

    log("Bus just departed");

    SDL_Delay(BUS_RIDE_DELAY);
}

int Bus::work() {
//    //Pre thread random seeding
//    srand(SDL_GetTicks());
//
//    //Wait randomly
//    SDL_Delay(16 + rand() % 32);

//    log("Acquiring lock for mutex");

    arrive();

    wait();

//    log("Lock for mutex acquired");

    depart();

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

    return 0;
}
