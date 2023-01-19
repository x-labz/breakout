#include <Pokitto.h>
#include "hal.h"

using PC = Pokitto::Core;

int16_t HAL::getPaddlePitch(void) {

    if (PC::buttons.leftBtn()) {
        return -10;
    }
    if (PC::buttons.rightBtn()) {
        return 10;
    }
    return 0;
}

uint32_t HAL::getTimeStamp(void) {
    return PC::getTime();
}

bool HAL::getAButton(void) {
    return PC::buttons.aBtn();
}

int16_t HAL::getRandom(uint16_t max ) {
    return  (rand() % max) ;
}