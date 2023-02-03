#pragma once

#include "inttypes.h"
#include "geometry-helpers.h"

// #define DASH_HEIGHT 20
// #define DISP_X 80
// #define DISP_Y 160 
// #define PLAY_AREA DISP_Y - DASH_HEIGHT 

// #define X_CNT 5
// #define X_OFF 1
// #define X_GAP 16
// #define W 14

// #define Y_CNT 6
// #define Y_OFF 10
// #define Y_GAP 12
// #define H 10

// #define PADDLE_W 20
// #define PADDLE_H 5
// #define BALL_R 2


#define DASH_HEIGHT 15
#define DISP_TOTAL_X 220
#define DISP_X 180
#define DISP_X_OFFSET (DISP_TOTAL_X - DISP_X) / 2
#define DISP_Y 176
#define PLAY_AREA DISP_Y - DASH_HEIGHT 

#define X_GAP 14
#define W 12
#define X_CNT (uint8_t)(DISP_X / X_GAP)
#define X_OFF (uint8_t)((DISP_X - (X_CNT * X_GAP)) / 2) 

#define Y_CNT 6
#define Y_OFF 10
#define Y_GAP 10
#define H  8

#define PADDLE_W 20
#define PADDLE_H 5
#define BALL_R 3

#define SURPRISE_Y_MIN Y_CNT * Y_GAP + Y_OFF
#define SURPRISE_Y_HEIGHT  30 
#define SURPRISE_R 10
#define SURPRISE_LIN_NUM 18

enum {
    BRICK_OFF,
    BRICK_LIGHT,
    BRICK_MEDIUM
};

enum {
    GAME_STATE_START,
    GAME_STATE_RDY,
    GAME_STATE_RUN,
    GAME_STATE_GAME_OVER,
    GAME_STATE_WIN
};

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t type;
    uint8_t blocker;
}
Brick_t;

enum {
    SURPRISE_NONE,
    SURPRISE_HEARTH,
    SURPRISE_MAX
};

enum {
    SURPRISE_STATUS_OFF,
    SURPRISE_STATUS_VISIBLE
};

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t type;
    uint32_t lifetime;
    uint32_t timestamp;
    uint8_t status;
    uint8_t progress ;
}
Surprise_t;

typedef struct {
    Surprise_t surprise;
    uint8_t lives;
    uint16_t score;
    bool lastBounceWasBrick;
    uint8_t game_state;
    Brick_t bricks[X_CNT * Y_CNT];
    uint16_t fps;
    int16_t paddle_x;
    int16_t paddle_speed;
    SQ15x16 ball_x;
    SQ15x16 ball_y;
    SQ15x16 ball_speed_x;
    SQ15x16 ball_speed_y;
    // int8_t brick_x;
    // int8_t brick_y;
    // Point_t coll_brick_p1;
    // Point_t coll_brick_p2;
    bool coll_brick_valid;
}
Breakout_store_t;