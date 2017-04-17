/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_image.h>

#include "LTexture.h"
#include "LTimer.h"
#include "Dot.h"

#include "constants.h"
#include "Worker.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Our worker thread function
int worker(void *data);

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Scene textures
LTexture *gDotTexture = NULL;

//Data access semaphore
SDL_sem *gDataLock = NULL;

//The "data buffer"
int gData = -1;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                gDotTexture = new LTexture(gRenderer);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia() {
    //Initialize semaphore
    gDataLock = SDL_CreateSemaphore(1);

    //Loading success flag
    bool success = true;

    //Load dot texture
    if (!gDotTexture->loadFromFile("../images/dot.bmp")) {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    return success;
}

void close() {
    //Free loaded images
    gDotTexture->free();

    //Free semaphore
    SDL_DestroySemaphore(gDataLock);
    gDataLock = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            int ids[] = {0, 1};
            Worker workerA(&gData, gDataLock, "Thread A");
            Worker workerB(&gData, gDataLock, "Thread B");

            //Run the threads
            srand(SDL_GetTicks());
            SDL_Thread *threadA = SDL_CreateThread(Worker::work, "Thread A", (void *) &workerA);
            SDL_Delay(16 + rand() % 32);
            SDL_Thread *threadB = SDL_CreateThread(Worker::work, "Thread B", (void *) &workerB);

            //The dot that will be moving around on the screen
            Dot dot;
            dot.setTexture(gDotTexture);

            //Keeps track of time between steps
            LTimer stepTimer;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    //Handle input for the dot
                    dot.handleEvent(e);
                }

                //Calculate time step
                float timeStep = stepTimer.getTicks() / 1000.f;

                //Move for time step
                dot.move(timeStep);

                //Restart step timer
                stepTimer.start();

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render dot
                dot.render();

                //Update screen
                SDL_RenderPresent(gRenderer);
            }

            //Wait for threads to finish
            SDL_WaitThread(threadA, NULL);
            SDL_WaitThread(threadB, NULL);
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}