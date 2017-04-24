#include "RiderShape.h"
#include "constants.h"

RiderShape::RiderShape() {
    status = RIDER_AWAY;
}

void RiderShape::draw(SDL_Renderer *renderer, int x, int y) {
    Uint32 riderColor = getColor();
    int w = RIDER_WIDTH;
    int h = RIDER_HEIGHT;

    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, R(riderColor), G(riderColor), B(riderColor), A(riderColor));
    SDL_RenderFillRect(renderer, &fillRect);
}

Uint32 RiderShape::getColor() {
    switch (status) {
        case RIDER_WAITING:
            return RIDER_WAITING_COLOR;
        case RIDER_BOARDING:
            return RIDER_BOARDING_COLOR;
        case RIDER_ARRIVING:
            return RIDER_ARRIVING_COLOR;
        case RIDER_AWAY:
            return RIDER_AWAY_COLOR;
    }
}