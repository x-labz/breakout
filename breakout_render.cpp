#include "Pokitto.h"
#include <PokittoFonts.h>
#include "breakout_render.h"
#include "breakout-store.h"
#include "brick.h"
#include "brick2.h"
#include "paddle.h"
#include "ball6.h"

using PD = Pokitto::Display;

void breakout_render(Breakout_store_t * store) {

    PD::setColor(1);
    PD::drawColumn(DISP_X_OFFSET + 0, 0, 175) ;
    PD::drawColumn(DISP_X_OFFSET + DISP_X - 1, 0, 175);
       PD::setColor(13);
    PD::drawColumn(DISP_X_OFFSET -1, 0, 175) ;
    PD::drawColumn(DISP_X_OFFSET + DISP_X , 0, 175);

    // // padle
    // PD::setColor(1);
    // PD::drawRect(DISP_X_OFFSET + 1 + store->paddle_x, PLAY_AREA - 1 - PADDLE_H, PADDLE_W, PADDLE_H);
    PD::drawBitmap(DISP_X_OFFSET + 1 + store->paddle_x, PLAY_AREA - 1 - PADDLE_H, paddle);

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