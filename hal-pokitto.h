#pragma once

#include "inttypes.h"

class HAL
{

public:
    HAL()
    {
        lastAButton = false;
    }
    static inline bool lastAButton;

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