#ifndef DOT_H
#define DOT_H

#include <SDL.h>

#include "constants.h"
#include "LTexture.h"

//The dot that will move around on the screen
class Dot {
public:
    //Initializes the variables
    Dot();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent(SDL_Event &e);

    //Moves the dot
    void move(float timeStep);

    //Shows the dot on the screen
    void render();

    void setRenderer(SDL_Renderer *gRenderer);

    void setPos(float x, float y);

    void setSize(int width, int height);

    void setColor(uint32_t color);

private:
    int width;
    int height;
    uint8_t r, g, b, alpha;
    float mPosX, mPosY;
    float mVelX, mVelY;
    SDL_Renderer *renderer;
};

#endif //PROJETO1_LDOT_H
