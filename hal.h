#pragma once

#include "inttypes.h"

class HAL {
    public:
        static int16_t getPaddlePitch(void);
        static uint32_t getTimeStamp(void);
        static bool getAButton(void) ;
        
};