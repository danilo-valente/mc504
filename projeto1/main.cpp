/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_image.h>

#include "LTexture.h"
#include "Dot.h"

#include "constants.h"
#include "Worker.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Scene textures
LTexture *gDotTexture = NULL;

//Data access semaphore
SDL_sem *gDataLock = NULL;

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
    int n = DEFAULT_N;
    int delay = DEFAULT_DELAY;
    int itr = DEFAULT_ITR;

    printf("Number of threads: ");
    scanf("%d", &n);

    printf("Delay: ");
    scanf("%d", &delay);

    printf("Iterations: ");
    scanf("%d", &itr);

    Worker *gWorkers[n];
    Dot gDots[n];

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

            for (int i = 0; i < n; i++) {
                gWorkers[i] = new Worker(i, gDots, n, delay, itr, gRenderer, gDataLock);
                gDots[i].setPos(DOT_WIDTH * i, 0);
                gDots[i].setRenderer(gRenderer);
                gDots[i].setSize(DOT_WIDTH, DOT_HEIGHT);
            }

            //Run the threads
            srand(SDL_GetTicks());

            SDL_Thread *threads[n];
            for (int i = 0; i < n; i++) {
                threads[i] = SDL_CreateThread(Worker::work, NULL, (void *) gWorkers[i]);
                SDL_Delay(16 + rand() % 32);
            }

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }

            //Wait for threads to finish
            for (int i = 0; i < n; i++) {
                SDL_WaitThread(threads[i], NULL);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}