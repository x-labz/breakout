#pragma once

#include "breakout-store.h"
#include "inttypes.h"

void createPattern(Breakout_store_t *store, uint8_t id)
{
    for (uint8_t y = 0; y != Y_CNT; y++)
    {
        for (uint8_t x = 0; x != X_CNT; x++)
        {
            store->bricks[x + y * (uint8_t)X_CNT] = {
                .x = (uint8_t)(X_OFF + X_GAP * x + 0),
                .y = (uint8_t)(Y_OFF + Y_GAP * y + 0),
                .type = BRICK_LIGHT,
                .blocker = 0};
        }
    }
    store->bricks[X_CNT / 2 + 0 * X_CNT].type = BRICK_MEDIUM;
    store->bricks[X_CNT / 2 + 2 * X_CNT].type = BRICK_MEDIUM;
    store->bricks[X_CNT / 2 + 4 * X_CNT].type = BRICK_MEDIUM;
    store->bricks[X_CNT / 2 - 3 + 2 * X_CNT].type = BRICK_MEDIUM;
    store->bricks[X_CNT / 2 + 3 + 2 * X_CNT].type = BRICK_MEDIUM;
}
