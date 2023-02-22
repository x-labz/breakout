

#include "stdio.h"
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
#include "hal.h"

void breakout_render_start(void)
{
    HAL::displaySetColor(9);
    char text[32];
    int16_t count = sprintf(text, "b r e a k o u t +");
    HAL::displaySetCursor((DISP_TOTAL_X - count * HAL::getFontCharX()) / 2 , 20);
    HAL::displayPrint(text);
    HAL::displaySetColor(15);
    count = sprintf(text, "x-labz.net");
    HAL::displaySetCursor((DISP_TOTAL_X - count * HAL::getFontCharX()) / 2 , DISP_Y - 25);
    HAL::displayPrint(text);
    HAL::displayDrawBitmap((DISP_TOTAL_X - breakout_logo[0]) / 2 - 6, (DISP_Y - breakout_logo[1]) / 2, breakout_logo);
}

void breakout_render(Breakout_store_t *store)
{

    if (store->game_state == GAME_STATE_START)
    {
        breakout_render_start();
        return;
    }

    if (DISP_X_OFFSET > 0)
    {
        HAL::displaySetColor(1);
        HAL::displayDrawColumn(DISP_X_OFFSET + 0, 0, DISP_Y - 1);
        HAL::displayDrawColumn(DISP_X_OFFSET + DISP_X - 1, 0, DISP_Y - 1);
        HAL::displaySetColor(13);
        HAL::displayDrawColumn(DISP_X_OFFSET - 1, 0, DISP_Y - 1);
        HAL::displayDrawColumn(DISP_X_OFFSET + DISP_X, 0, DISP_Y - 1);
    }

    // LIVES -HEARTH

    for (uint8_t i = 0; i != store->lives; i++)
    {
        HAL::displayDrawBitmap(HEARTH_X_OFFSET + HEARTH_X_ADVANCE * i, HEARTH_Y_OFFSET + HEARTH_Y_ADVANCE * i, hearth);
    }

    // // padle

    HAL::displayDrawBitmap(DISP_X_OFFSET + 1 + store->paddle_x, PLAY_AREA - 1 - PADDLE_H, store->paddle_width > PADDLE_W ? paddle_w : paddle);

    // bricks
    for (uint8_t i = 0; i != X_CNT * Y_CNT; i++)
    {
        if (store->bricks[i].type != 0)
        {
            HAL::displayDrawBitmap(DISP_X_OFFSET + store->bricks[i].x, store->bricks[i].y, store->bricks[i].type == 2 ? brick2 : brick);
        }
    }

    // ball

    HAL::displayDrawBitmap(DISP_X_OFFSET + store->ball_x - BALL_R, store->ball_y - BALL_R, ball6);

    // surprise

    Surprise_t *surprise_p = &(store->surprise);
    if (surprise_p->status == SURPRISE_STATUS_VISIBLE && surprise_p->type != SURPRISE_NONE)
    {
        const uint8_t *bitmap = surprises[surprise_p->type - 1].bitmap;

        HAL::displayDrawBitmap(DISP_X_OFFSET + surprise_p->x - bitmap[0] / 2, surprise_p->y - bitmap[1] / 2, bitmap);

        float x0 = DISP_X_OFFSET + surprise_p->x;
        float y0 = surprise_p->y;

        HAL::displaySetColor(11);
        for (uint8_t i = 0; i != SURPRISE_LIN_NUM; i++)
        {
            if (i <= surprise_p->progress)
                continue;
            HAL::displayDrawLine(x0 + SURPRISE_R * cos_table[4 * i], y0 + SURPRISE_R * sin_table[4 * i], x0 + SURPRISE_R * cos_table[(4 * (i + 1)) % 72], y0 + SURPRISE_R * sin_table[(4 * (i + 1)) % 72]);
        };
    }
    if (surprise_p->type == SURPRISE_BOMB && surprise_p->status == SURPRISE_STATUS_RUN)
    {
        HAL::displaySetColor(6);
        HAL::displayDrawCircle(DISP_X_OFFSET + surprise_p->x, surprise_p->y, surprise_p->progress);
    }
    if (surprise_p->type == SURPRISE_RAM && surprise_p->status == SURPRISE_STATUS_RUN)
    {
        HAL::displaySetColor(6);
        HAL::displayDrawCircle(DISP_X_OFFSET + store->ball_x - 1, store->ball_y - 1, 6);
    }

    // fps

    char text[32];
    HAL::displaySetColor(5);
    int16_t count = sprintf(text, "fps %d", store->fps);
    HAL::displaySetCursor(DISP_X_OFFSET + (DISP_X - count * HAL::getFontCharX()) / 2, 0);
    HAL::displayPrint(text);

    // score
    HAL::displaySetColor(9);
    count = sprintf(text, "score %d", store->score);
    HAL::displaySetCursor(DISP_X_OFFSET + (DISP_X - count * HAL::getFontCharX()) / 2, DISP_Y - 12);
    HAL::displayPrint(text);

    if (store->game_state == GAME_STATE_RDY)
    {
        HAL::displaySetColor(14);
        int16_t count = sprintf(text, "Get ready!");
        HAL::displaySetCursor(DISP_X_OFFSET + (DISP_X - count * HAL::getFontCharX()) / 2, DISP_Y / 2 + 5);
        HAL::displayPrint(text);
    }

    if (store->game_state == GAME_STATE_GAME_OVER)
    {
        HAL::displaySetColor(4);
        int16_t count = sprintf(text, "Game over!");
        HAL::displaySetCursor(DISP_X_OFFSET + (DISP_X - count * HAL::getFontCharX()) / 2, DISP_Y / 2 + 5);
        HAL::displayPrint(text);
    }

    if (store->game_state == GAME_STATE_WIN)
    {
        HAL::displaySetColor(15);
        int16_t count = sprintf(text, "You win!");
        HAL::displaySetCursor(DISP_X_OFFSET + (DISP_X - count * HAL::getFontCharX()) / 2, DISP_Y / 2 + 5);
        HAL::displayPrint(text);
    }
}