#ifndef CONSTANTS_H
#define CONSTANTS_H

//Screen dimension constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define WORKER_SETUP_DELAY      1000

#define STREET_WIDTH            ((int) (SCREEN_WIDTH * 0.67))
#define STREET_HEIGHT           SCREEN_HEIGHT
#define STREET_COLOR            0x2b2b2bff

#define STREET_PATH_WIDTH       20
#define STREET_PATH_HEIGHT      80
#define STREET_HALF_WIDTH       ((int) (STREET_WIDTH / 2))
#define STREET_PATH_SPACING     60
#define STREET_PATH_COLOR       0xffffffff

#define STREET_SIDEWALK_COLOR   0xccccccff

#define BUS_ARRIVAL_DELAY       250*20
#define BUS_DEPARTURE_DELAY     500*20
#define BUS_RIDE_DELAY          5000
#define BUS_SEATS               2
#define BUS_WAITING_COLOR       0xdddd00ff
#define BUS_DEPARTING_COLOR     0xdd0000ff
#define BUS_MARGIN              20
#define BUS_BASE_X              (STREET_HALF_WIDTH + STREET_PATH_WIDTH / 2 + BUS_MARGIN)
#define BUS_BASE_Y              40
#define BUS_WIDTH               ((int) ((STREET_WIDTH - STREET_PATH_WIDTH) / 2 - BUS_MARGIN * 2))
#define BUS_HEIGHT              500

#define RIDER_ARRIVAL_DELAY     100*20
#define RIDER_BOARDING_DELAY    50*20
#define RIDER_COLOR             0xffe495ff

#define R(c) ((Uint8) (((c) >> 24) & 0xff))
#define G(c) ((Uint8) (((c) >> 16) & 0xff))
#define B(c) ((Uint8) (((c) >> 8) & 0xff))
#define A(c) ((Uint8) ((c) & 0xff))

#define DOT_WIDTH 20
#define DOT_HEIGHT 20
#define DOT_VEL 640

#define COLOR_RED   0xFF0000FF
#define COLOR_GREEN 0x00FF00FF

#endif
