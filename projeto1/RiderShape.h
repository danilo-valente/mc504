#ifndef RIDER_SHAPE_H
#define RIDER_SHAPE_H

#include <SDL.h>
#include "RiderStatus.h"
#include "Shape.h"

class RiderShape : public Shape {
public:
    RiderStatus status;

    RiderShape();

    void draw(SDL_Renderer *renderer, int x, int y);
};

#endif
