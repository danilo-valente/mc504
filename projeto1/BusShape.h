#ifndef BUS_SHAPE_H
#define BUS_SHAPE_H

#include <SDL.h>
#include "BusStatus.h"
#include "Shape.h"

class BusShape : public Shape {
public:
    BusStatus status;

    BusShape();

    void draw(SDL_Renderer *renderer, int x, int y);
};

#endif
