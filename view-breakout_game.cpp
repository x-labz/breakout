
#include "display.h"
#include "view-breakout_game.h"
#include "breakout-store.h"
#include "breakout_systems.h"
#include "breakout_render.h"
#include "hal.h"

bool view_breakout_game(void)
{
    printf("view-breakout \n");
    LGFX_Sprite *fb = Display::fb_sprite;
    Breakout_store_t store;

    bool keep_running = true;

    breakout_init(&store);
    printf("init done\n");

    while (keep_running)
    {
        fb->pushSprite(0, 0);
        fb->fillSprite(0);
        breakout_render(&store);
        keep_running = breakout_run();
        
        vTaskDelay(2);
    }

    GlobalState::currentView = WATCH;

    printf("view end\n");

    printf("deleting sprite\n");
    fb->deleteSprite();
    printf("returning\n");

    return true;
}