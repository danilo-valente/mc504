#include <iostream>
#include "Street.h"
#include "constants.h"

Street::Street(SDL_Renderer *renderer) {
    this->renderer = renderer;
    drawing = SDL_CreateSemaphore(1);
}

Street::~Street() {
    SDL_DestroySemaphore(drawing);
}

void Street::addBus(BusShape *bus) {
    buses.push_back(bus);
}

void Street::addRider(RiderShape *rider) {
    riders.push_back(rider);
}

void Street::draw() {
    SDL_SemWait(drawing);

    SDL_SetRenderDrawColor(renderer, R(STREET_COLOR), G(STREET_COLOR), B(STREET_COLOR), A(STREET_COLOR));
    SDL_RenderClear(renderer);

    drawStreet();
    drawSidewalk();

    drawCurrentBus();
    drawBoardingRider();
    drawWaitingRiders();

    SDL_RenderPresent(renderer);

    SDL_SemPost(drawing);
}

void Street::drawStreet() {
    Uint32 pathColor = STREET_PATH_COLOR;
    int w = STREET_PATH_WIDTH;
    int h = STREET_PATH_HEIGHT;
    int s = STREET_PATH_SPACING;
    int y, x = (STREET_WIDTH - w) / 2;
    int i, n = (int) ceil(STREET_HEIGHT / h);

    for (i = 0; i < n; i++) {
        y = h * i + s * (i - 1);
        SDL_Rect fillRect = {x, y, w, h};
        SDL_SetRenderDrawColor(renderer, R(pathColor), G(pathColor), B(pathColor), A(pathColor));
        SDL_RenderFillRect(renderer, &fillRect);
    }
}

void Street::drawSidewalk() {
    Uint32 sidewalkColor = SIDEWALK_COLOR;
    int x = SIDEWALK_X;
    int y = SIDEWALK_Y;
    int w = SIDEWALK_WIDTH;
    int h = SIDEWALK_HEIGHT;

    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, R(sidewalkColor), G(sidewalkColor), B(sidewalkColor), A(sidewalkColor));
    SDL_RenderFillRect(renderer, &fillRect);
}

void Street::drawCurrentBus() {
    BusShape *bus = findCurrentBus();
    if (bus != NULL) {
        bus->draw(renderer, BUS_BASE_X, BUS_BASE_Y);
    }
}

void Street::drawBoardingRider() {
    RiderShape *rider = findBoardingRider();
    if (rider != NULL) {
        rider->draw(renderer, RIDER_BASE_X, RIDER_BASE_Y);
    }
}

void Street::drawWaitingRiders() {
    vector<RiderShape *>::iterator itr;
    int r = RIDER_ROW_LENGTH - 1;
    int i = 0;

    // Draw waiting riders
    itr = riders.begin();
    while (itr != riders.end()) {
        if ((*itr)->status == RIDER_WAITING) {
            drawRider(*itr, r, &i);
        }

        itr++;
    }

    i = (int) ceil(i / r) * r;

    // Draw arriving riders
    itr = riders.begin();
    while (itr != riders.end()) {
        if ((*itr)->status == RIDER_ARRIVING) {
            drawRider(*itr, r, &i);
        }

        itr++;
    }
}

void Street::drawRider(RiderShape *shape, int r, int *i) {
    int x = RIDER_BASE_X + (1 + *i % r) * (RIDER_WIDTH + RIDER_SPACING);
    int y = RIDER_BASE_Y + (*i / r) * (RIDER_HEIGHT + RIDER_SPACING);
    shape->draw(renderer, x, y);
    (*i)++;
}

BusShape * Street::findCurrentBus() {
    vector<BusShape *>::iterator itr = buses.begin();
    while (itr != buses.end()) {
        if ((*itr)->status == BUS_WAITING || (*itr)->status == BUS_DEPARTING) {
            return *itr;
        }

        itr++;
    }

    return NULL;
}

RiderShape * Street::findBoardingRider() {
    vector<RiderShape *>::iterator itr = riders.begin();
    while (itr != riders.end()) {
        if ((*itr)->status == RIDER_BOARDING) {
            return *itr;
        }

        itr++;
    }

    return NULL;
}