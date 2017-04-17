#include "Dot.h"

Dot::Dot() {
    r = 0;
    g = 0;
    b = 0;
    alpha = 0;

    width = 0;
    height = 0;

    //Initialize the position
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    renderer = NULL;
}

void Dot::setPos(float x, float y) {
    mPosX = x;
    mPosY = y;
}

void Dot::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

void Dot::setColor(uint32_t color) {
    this->r = (uint8_t) (color >> 24);
    this->g = (uint8_t) (color >> 16);
    this->b = (uint8_t) (color >> 8);
    this->alpha = (uint8_t) color;
}

void Dot::handleEvent(SDL_Event &e) {
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVelY -= DOT_VEL;
                break;
            case SDLK_DOWN:
                mVelY += DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelX -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelX += DOT_VEL;
                break;
        }
    }
        //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVelY += DOT_VEL;
                break;
            case SDLK_DOWN:
                mVelY -= DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelX += DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelX -= DOT_VEL;
                break;
        }
    }
}

void Dot::move(float timeStep) {
    //Move the dot left or right
    mPosX += mVelX * timeStep;

    //If the dot went too far to the left or right
    if (mPosX < 0) {
        mPosX = 0;
    } else if (mPosX > SCREEN_WIDTH - DOT_WIDTH) {
        mPosX = SCREEN_WIDTH - DOT_WIDTH;
    }

    //Move the dot up or down
    mPosY += mVelY * timeStep;

    //If the dot went too far up or down
    if (mPosY < 0) {
        mPosY = 0;
    } else if (mPosY > SCREEN_HEIGHT - DOT_HEIGHT) {
        mPosY = SCREEN_HEIGHT - DOT_HEIGHT;
    }
}

void Dot::render() {
    SDL_Rect fillRect = {(int) (mPosX + mPosX / width), (int) (mPosY + mPosY / height), width, height};
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &fillRect);
}

void Dot::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
}