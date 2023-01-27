#include "breakout_systems_surprises.h"
#include "stdio.h"
#include "hal.h"

void generateSurprise( Breakout_store_t * p ) {
    Surprise_t * surprise_p = &(p->surprise) ;
    
    if ( surprise_p->type != SURPRISE_NONE ) return ;
    
    surprise_p->timestamp = 2000 + HAL::getRandom(4000) + HAL::getTimeStamp() ;
    surprise_p->lifetime = 5000 ;
    surprise_p->type = 1 + HAL::getRandom(SURPRISE_MAX-1) ;
    surprise_p->x = X_OFF + HAL::getRandom(DISP_X - X_OFF * 2) ;
    surprise_p->y = SURPRISE_Y_MIN + HAL::getRandom(SURPRISE_Y_HEIGHT) ;
}


