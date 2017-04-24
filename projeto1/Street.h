#ifndef STREET_H
#define STREET_H

#include <vector>
#include <SDL.h>
#include "BusShape.h"
#include "RiderShape.h"

using namespace std;

class Street {
public:
    Street(SDL_Renderer *renderer);
    ~Street();

    void addBus(BusShape *bus);
    void addRider(RiderShape *rider);
    void draw();

private:
    SDL_sem *drawing;
    SDL_Renderer *renderer;
    vector<BusShape *> buses;
    vector<RiderShape *> riders;

    void drawStreet();
    void drawSidewalk();
    void drawCurrentBus();

    BusShape * findCurrentBus();
};


#endif
