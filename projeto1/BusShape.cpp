#include "BusShape.h"
#include "constants.h"

BusShape::BusShape() {
    status = BUS_AWAY;
}

void BusShape::draw(SDL_Renderer *renderer, int x, int y) {
    Uint32 busColor = status == BUS_WAITING ? BUS_WAITING_COLOR : BUS_DEPARTING_COLOR;
    int w = BUS_WIDTH;
    int h = BUS_HEIGHT;

    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, R(busColor), G(busColor), B(busColor), A(busColor));
    SDL_RenderFillRect(renderer, &fillRect);
}