#include "breakout_systems_surprises.h"
#include "stdio.h"
#include "hal.h"
#include "surprises.h"
#include "math.h"

void surpriseSystem(Breakout_store_t * p) {
    generateSurprise(p);
    run(p);
    checkSurpriseHit(p);
}

void generateSurprise(Breakout_store_t * p) {
    Surprise_t * surprise_p = & (p->surprise);

    if (surprise_p->type != SURPRISE_NONE)
        return;

    surprise_p->x = X_OFF + SURPRISE_R + HAL::getRandom(DISP_X - (X_OFF + SURPRISE_R) * 2);
    surprise_p->y = SURPRISE_Y_MIN + HAL::getRandom(SURPRISE_Y_HEIGHT);

    if (abs(surprise_p->x - (int16_t) p->ball_x) < 35 && abs(surprise_p->y - (int16_t) p->ball_y) < 35)
        return;

    surprise_p->timestamp = 2000 + HAL::getRandom(4000) + HAL::getTimeStamp();
    surprise_p->lifetime = 15000;
    surprise_p->type = 1 + (uint8_t) HAL::getRandom(SURPRISE_MAX - 1);

    if (surprise_p->type > 0) {
        ( * surprises[surprise_p->type - 1].generate)(surprise_p, p);
    }

    surprise_p->status = SURPRISE_STATUS_OFF;
}

void run(Breakout_store_t * p) {
    Surprise_t * surprise_p = & (p->surprise);
    uint32_t now = HAL::getTimeStamp();
    if (now > surprise_p->timestamp && surprise_p->status == SURPRISE_STATUS_OFF) {
        surprise_p->status = SURPRISE_STATUS_VISIBLE;
    }
    if (surprise_p->status == SURPRISE_STATUS_VISIBLE && now > surprise_p->timestamp + surprise_p->lifetime) {
        surprise_p->status = SURPRISE_STATUS_OFF;
        surprise_p->type = SURPRISE_NONE;
    }
    if (surprise_p->status == SURPRISE_STATUS_RUN && now > surprise_p->timestamp + surprise_p->lifetime) {
        if (surprise_p->type > 0)
            ( * surprises[surprise_p->type - 1].destroy)(surprise_p, p);
        surprise_p->status = SURPRISE_STATUS_OFF;
        surprise_p->type = SURPRISE_NONE;
    }
    if (surprise_p->status == SURPRISE_STATUS_VISIBLE) {
        surprise_p->progress = (uint8_t)(((now - surprise_p->timestamp) * SURPRISE_LIN_NUM) / surprise_p->lifetime);
    }
    if (surprise_p->status == SURPRISE_STATUS_RUN) {
        if (surprise_p->type > 0) {
            ( * surprises[surprise_p->type - 1].run)(surprise_p, p);
        }
    }
}

void checkSurpriseHit(Breakout_store_t * p) {
    Surprise_t * surprise_p = & (p->surprise);
    if (surprise_p->status != SURPRISE_STATUS_VISIBLE)
        return;

    int16_t dx = surprise_p->x - (int16_t)(p->ball_x);
    int16_t dy = surprise_p->y - (int16_t)(p->ball_y);
    int16_t d2 = (BALL_R + SURPRISE_R) * (BALL_R + SURPRISE_R);
    if (dx * dx + dy * dy < d2) {
        surprise_p->status = SURPRISE_STATUS_RUN;
        uint32_t now = HAL::getTimeStamp();
        surprise_p->timestamp = now;
        if (surprise_p->type > 0) {
            ( * surprises[surprise_p->type - 1].hit)(surprise_p, p);
        }
    }
}