#include "Pokitto.h"
#include <PokittoFonts.h>
#include "breakout_render.h"
#include "breakout-store.h"
#include "brick.h"
#include "brick2.h"
#include "paddle.h"
#include "paddle_w.h"
#include "ball6.h"
#include "hearth.h"
#include "breakout_logo.h"
#include "math.h"
#include "math-helpers.h"
#include "surprises.h"


using PD = Pokitto::Display;


void breakout_render_start(void) {
    PD::setColor(9);
    char text[32];
    int16_t count = sprintf(text, "b r e a k o u t +");
    PD::setCursor((DISP_TOTAL_X - count * fontZXSpec[0]) / 2 + 15, 20);
    PD::print(text);
    PD::setColor(15);
    count = sprintf(text, "x-labz.net");
    PD::setCursor((DISP_TOTAL_X - count * fontZXSpec[0]) / 2 + 4, DISP_Y - 25);
    PD::print(text);

    PD::drawBitmap((DISP_TOTAL_X - breakout_logo[0]) / 2 - 6, (DISP_Y - breakout_logo[1]) / 2, breakout_logo);

}

void breakout_render(Breakout_store_t * store) {

    if (store->game_state == GAME_STATE_START) {
        breakout_render_start();
        return;
    }

    PD::setColor(1);
    PD::drawColumn(DISP_X_OFFSET + 0, 0, 175);
    PD::drawColumn(DISP_X_OFFSET + DISP_X - 1, 0, 175);
    PD::setColor(13);
    PD::drawColumn(DISP_X_OFFSET - 1, 0, 175);
    PD::drawColumn(DISP_X_OFFSET + DISP_X, 0, 175);

    for (uint8_t i = 0; i != store->lives; i++) {
        PD::drawBitmap(5, 5 + 16 * i, hearth);
    }

    // // padle
    // PD::setColor(1);
    // PD::drawRect(DISP_X_OFFSET + 1 + store->paddle_x, PLAY_AREA - 1 - PADDLE_H, PADDLE_W, PADDLE_H);
    PD::drawBitmap(DISP_X_OFFSET + 1 + store->paddle_x, PLAY_AREA - 1 - PADDLE_H, store->paddle_width > PADDLE_W ? paddle_w : paddle);
    

    // bricks
    for (uint8_t i = 0; i != X_CNT * Y_CNT; i++) {
        // PD::setColor(store->bricks[i].type == 2 ? 2 : 1);
        if (store->bricks[i].type != 0) {
            // PD::drawRect(DISP_X_OFFSET + store->bricks[i].x, store->bricks[i].y, W, H);
            PD::drawBitmap(DISP_X_OFFSET + store->bricks[i].x, store->bricks[i].y, store->bricks[i].type == 2 ? brick2 : brick);

        }
    }

    // ball

    // PD::setColor(3);
    // PD::fillCircle(DISP_X_OFFSET + store->ball_x, store->ball_y, BALL_R);
    PD::drawBitmap(DISP_X_OFFSET + store->ball_x - BALL_R, store->ball_y - BALL_R, ball6);

    // surprise

    Surprise_t * surprise_p = & (store->surprise);
    if (surprise_p->status == SURPRISE_STATUS_VISIBLE && surprise_p->type != SURPRISE_NONE) {
        const uint8_t * bitmap = surprises[surprise_p->type - 1].bitmap;
        
        PD::drawBitmap(DISP_X_OFFSET + surprise_p->x - bitmap[0] / 2 , surprise_p->y - bitmap[1] / 2 , bitmap);

        float x0 = DISP_X_OFFSET + surprise_p->x;
        float y0 = surprise_p->y;

        PD::setColor(11);
        for (uint8_t i = 0; i != SURPRISE_LIN_NUM; i++) {
            if (i <= surprise_p->progress) continue;
            PD::drawLine(x0 + SURPRISE_R * cos_table[4 * i], y0 + SURPRISE_R * sin_table[4 * i], x0 + SURPRISE_R * cos_table[(4 * (i + 1)) % 72], y0 + SURPRISE_R * sin_table[(4 * (i + 1)) % 72]);
        };

    }


// fps

char text[32];
PD::setColor(5);
int16_t count = sprintf(text, "fps %d", store->fps);
PD::setCursor(DISP_X_OFFSET + (DISP_X - count * fontZXSpec[0]) / 2, 0);
PD::print(text);

// score
PD::setColor(9);
count = sprintf(text, "score %d", store->score);
PD::setCursor(DISP_X_OFFSET + (DISP_X - count * fontZXSpec[0]) / 2, DISP_Y - 12);
PD::print(text);

if (store->game_state == GAME_STATE_RDY) {
    PD::setColor(14);
    int16_t count = sprintf(text, "Get ready!");
    PD::setCursor(DISP_X_OFFSET + (DISP_X - count * fontZXSpec[0]) / 2, DISP_Y / 2 + 5);
    PD::print(text);
}

if (store->game_state == GAME_STATE_GAME_OVER) {
    PD::setColor(4);
    int16_t count = sprintf(text, "Game over!");
    PD::setCursor(DISP_X_OFFSET + (DISP_X - count * fontZXSpec[0]) / 2, DISP_Y / 2 + 5);
    PD::print(text);

}

if (store->game_state == GAME_STATE_WIN) {
    PD::setColor(15);
    int16_t count = sprintf(text, "You win!");
    PD::setCursor(DISP_X_OFFSET + (DISP_X - count * fontZXSpec[0]) / 2, DISP_Y / 2 + 5);
    PD::print(text);

}


}