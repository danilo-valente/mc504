#ifndef SHAPE_H
#define SHAPE_H

#include <SDL.h>

class Shape {
public:
    virtual void draw(SDL_Renderer *renderer, int x, int y) = 0;
};

#endif
