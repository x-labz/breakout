#include "Pokitto.h"
#include <PokittoFonts.h>
#include "breakout_render.h"
#include "breakout-store.h"

using PD = Pokitto::Display;

void breakout_render(Breakout_store_t * store) {

    PD::setFont(fontZXSpec);
    PD::setColor(1);

    PD::drawLine(DISP_X_OFFSET + 0, 0, DISP_X_OFFSET + DISP_X - 1, 0);
    PD::drawLine(DISP_X_OFFSET + 0, 0, DISP_X_OFFSET + 0, DISP_Y - 1);
    PD::drawLine(DISP_X_OFFSET + DISP_X - 1, 0, DISP_X_OFFSET + DISP_X - 1, DISP_Y - 1);

    // // padle
    PD::setColor(1);
    PD::drawRect(DISP_X_OFFSET + 1 + store->paddle_x, PLAY_AREA - 1 - PADDLE_H, PADDLE_W, PADDLE_H);

    // bricks
    for (uint8_t i = 0; i != X_CNT * Y_CNT; i++) {
        PD::setColor(store->bricks[i].type == 2 ? 2 : 1);
        if (store->bricks[i].type != 0) {
            PD::drawRect(DISP_X_OFFSET + store->bricks[i].x, store->bricks[i].y, W, H);
        }
    }

    // ball

    PD::setColor(3);
    PD::fillCircle(DISP_X_OFFSET + store->ball_x, store->ball_y, BALL_R);

    // colors
    for (uint8_t i = 0; i != 16; i++) {
        PD::setColor(i);
        PD::fillRectangle(0 , 0 + i * 10 , 7, 10);
    }

    char text[32];
    sprintf(text, "fps %d", store->fps);
    PD::setCursor(DISP_X_OFFSET + 0, DISP_Y - 20);
    PD::print(text);

    int16_t count = sprintf(text, "score %d", store->score);
    PD::setCursor(DISP_X_OFFSET + (DISP_X - count * fontZXSpec[0]) / 2, DISP_Y - 10);
    PD::print(text);

    if (store->game_state == GAME_STATE_RDY) {
        PD::setColor(3);
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
        PD::setColor(4);
        int16_t count = sprintf(text, "You win!");
        PD::setCursor(DISP_X_OFFSET + (DISP_X - count * fontZXSpec[0]) / 2, DISP_Y / 2 + 5);
        PD::print(text);

    }


}