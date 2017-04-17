#ifndef DOT_H
#define DOT_H

#include <SDL.h>

#include "constants.h"
#include "LTexture.h"

//The dot that will move around on the screen
class Dot {
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 640;

    //Initializes the variables
    Dot();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent(SDL_Event &e);

    //Moves the dot
    void move(float timeStep);

    //Shows the dot on the screen
    void render();

    void setTexture(LTexture *gDotTexture);

    void setPos(float x, float y);

private:
    float mPosX, mPosY;
    float mVelX, mVelY;
    LTexture *gDotTexture;
};

#endif //PROJETO1_LDOT_H
