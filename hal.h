#pragma once

#include "inttypes.h"

class HAL {
   
    public:
         HAL() {
            lastAButton = false;
        }
    static inline bool lastAButton;
    static int16_t getPaddlePitch(void);
    static uint32_t getTimeStamp(void);
    static bool getAButton(void);
    static int16_t getRandom(uint16_t max);
};