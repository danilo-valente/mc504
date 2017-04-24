#ifndef CONSTANTS_H
#define CONSTANTS_H

//Screen dimension constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define WORKER_SETUP_DELAY      1000
#define WORKER_RAND_RANGE       1024
#define WORKER_RAND_VARIATION   0.2

#define STREET_WIDTH            ((int) (SCREEN_WIDTH * 0.67))
#define STREET_HEIGHT           SCREEN_HEIGHT
#define STREET_COLOR            0x2b2b2bff

#define STREET_PATH_WIDTH       20
#define STREET_PATH_HEIGHT      80
#define STREET_HALF_WIDTH       ((int) (STREET_WIDTH / 2))
#define STREET_PATH_SPACING     60
#define STREET_PATH_COLOR       0xffffffff

#define SIDEWALK_X              STREET_WIDTH
#define SIDEWALK_Y              0
#define SIDEWALK_WIDTH          (SCREEN_WIDTH - SIDEWALK_X)
#define SIDEWALK_HEIGHT         (SCREEN_HEIGHT - SIDEWALK_Y)
#define SIDEWALK_COLOR          0xaaaaaaff

#define BUS_ARRIVAL_DELAY       250
#define BUS_DEPARTURE_DELAY     500
#define BUS_RIDE_DELAY          5000
#define BUS_SEATS               50
#define BUS_WAITING_COLOR       0xdddd00ff
#define BUS_DEPARTING_COLOR     0xdd0000ff
#define BUS_MARGIN              20
#define BUS_BASE_X              (STREET_HALF_WIDTH + STREET_PATH_WIDTH / 2 + BUS_MARGIN)
#define BUS_BASE_Y              40
#define BUS_WIDTH               ((int) ((STREET_WIDTH - STREET_PATH_WIDTH) / 2 - BUS_MARGIN * 2))
#define BUS_HEIGHT              500

#define RIDER_ARRIVAL_DELAY     500
#define RIDER_BOARDING_DELAY    250
#define RIDER_RIDE_DELAY        6500
#define RIDER_BOARDING_COLOR    0x00cc00ff
#define RIDER_WAITING_COLOR     0xffe495ff
#define RIDER_ARRIVING_COLOR    0x990000ff
#define RIDER_AWAY_COLOR        0x00000000
#define RIDER_SPACING           10
#define RIDER_BASE_X            (SIDEWALK_X + RIDER_SPACING)
#define RIDER_BASE_Y            (SIDEWALK_Y + RIDER_SPACING)
#define RIDER_ROW_LENGTH        9
#define RIDER_WIDTH             ((int) (((SIDEWALK_WIDTH - RIDER_SPACING) / RIDER_ROW_LENGTH) - RIDER_SPACING))
#define RIDER_HEIGHT            RIDER_WIDTH

#define R(c) ((Uint8) (((c) >> 24) & 0xff))
#define G(c) ((Uint8) (((c) >> 16) & 0xff))
#define B(c) ((Uint8) (((c) >> 8) & 0xff))
#define A(c) ((Uint8) ((c) & 0xff))

#endif
