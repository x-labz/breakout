#pragma once

#include "breakout-store.h"

void createPattern(Breakout_store_t * store, uint8_t id) {
    for (uint8_t y = 0; y != Y_CNT; y++) {
         for (uint8_t x = 0; x != X_CNT; x++) {
             store->bricks[x + y * X_CNT] = {
                 .x = X_OFF + X_GAP * x + 0,
                 .y = Y_OFF + Y_GAP * y + 0,
                 .type = (x == 3 || x == 1) && (y == 2 || y == 3) ? BRICK_MEDIUM : BRICK_LIGHT,
                 .blocker = 0
             };
         }
     }
}

