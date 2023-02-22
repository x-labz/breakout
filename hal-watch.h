#pragma once

#include "inttypes.h"

#define DASH_HEIGHT 15
#define DISP_TOTAL_X 80
#define DISP_X 80
#define DISP_X_OFFSET (DISP_TOTAL_X - DISP_X) / 2
#define DISP_Y 160
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
#define SURPRISE_Y_HEIGHT  35
#define SURPRISE_R 10
#define SURPRISE_LIN_NUM 18

#define SURPRISE_BOMB_SPEED 2
#define SURPRISE_BOMB_DIST 35

#define HEARTH_X_ADVANCE 16
#define HEARTH_Y_ADVANCE 16
#define HEARTH_X_OFFSET 0
#define HEARTH_Y_OFFSET 0


class HAL
{

public:
    HAL()
    {
        lastAButton = false;
    }
    static inline bool lastAButton;
    static inline uint8_t invisibleColor ;
    static inline uint8_t color;
    static inline uint16_t cursor_x, cursor_y;
    static inline uint32_t last_btn ;

    static void init(void);
    static void displaySetColor(uint8_t color);
    static void displaySetCursor(uint16_t x, uint16_t y);
    static void displayPrint(char * text);
    static void displayDrawBitmap(int16_t x, int16_t y, const uint8_t * data);
    static void displayDrawColumn(int16_t x, int16_t y, int16_t len) ; 
    static void displayDrawCircle(int16_t x, int16_t y, int16_t r);
    static void displayDrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    static uint16_t getFontCharX(void);
    static int16_t getPaddlePitch(void);
    static uint32_t getTimeStamp(void);
    static bool getAButton(void);
    static int16_t getRandom(uint16_t max);
};