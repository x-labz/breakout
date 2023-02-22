#pragma once

#include "inttypes.h"
#include "geometry-helpers.h"
#include "hal.h"

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
    SURPRISE_INC_SPEED,
    SURPRISE_INC_PADDLE_W,
    SURPRISE_BOMB,
    SURPRISE_RAM,
    SURPRISE_MAX
};

enum {
    SURPRISE_STATUS_OFF,
    SURPRISE_STATUS_VISIBLE,
    SURPRISE_STATUS_RUN
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
    bool disableBrickBounce;
    uint8_t game_state;
    Brick_t bricks[X_CNT * Y_CNT];
    uint16_t fps;
    int16_t paddle_x;
    int16_t paddle_speed;
    float ball_x;
    float ball_y;
    float ball_speed_x;
    float ball_speed_y;
    bool coll_brick_valid;
    uint8_t paddle_width;
}
Breakout_store_t;