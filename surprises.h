#pragma once 

#include "breakout-store.h"
#include "hearth.h"
#include "surprise_inc_speed.h"
#include "surprise_inc_paddle_w.h"
#include "bomb.h"
#include "ram.h"

typedef struct {
    void( * generate)(Surprise_t * surprise, Breakout_store_t * p);
    void( * hit)(Surprise_t * surprise, Breakout_store_t * p);
    void( * run)(Surprise_t * surprise, Breakout_store_t * p);
    void( * destroy)(Surprise_t * surprise, Breakout_store_t * p);
    const uint8_t * bitmap;

}
Surprise_def_t;

void surprise_dummy_handler(Surprise_t * surprise_p, Breakout_store_t * p);

void hearth_generate(Surprise_t * surprise, Breakout_store_t * p);
void hearth_hit(Surprise_t * surprise, Breakout_store_t * p);
void hearth_run(Surprise_t * surprise, Breakout_store_t * p);

void inc_speed_generate(Surprise_t * surprise, Breakout_store_t * p);
void inc_speed_hit(Surprise_t * surprise, Breakout_store_t * p);
void inc_speed_run(Surprise_t * surprise, Breakout_store_t * p);
void inc_speed_destroy(Surprise_t * surprise_p, Breakout_store_t * p);

void inc_paddle_w_hit(Surprise_t * surprise_p, Breakout_store_t * p);
void inc_paddle_w_destroy(Surprise_t * surprise_p, Breakout_store_t * p);

void bomb_hit(Surprise_t * surprise_p, Breakout_store_t * p) ;
void bomb_run(Surprise_t * surprise_p, Breakout_store_t * p) ;

void ram_hit(Surprise_t * surprise_p, Breakout_store_t * p);
void ram_run(Surprise_t * surprise_p, Breakout_store_t * p);

static Surprise_def_t surprises[] = {
    { & hearth_generate, & hearth_hit, & hearth_run, & surprise_dummy_handler, hearth
    },
    { & inc_speed_generate,
        & inc_speed_hit,
        & inc_speed_run,
        & inc_speed_destroy,
        surprise_inc_speed
    },
    {
        & surprise_dummy_handler,&inc_paddle_w_hit,& surprise_dummy_handler,&inc_paddle_w_destroy, surprise_inc_paddle_w
    },
    {
        & surprise_dummy_handler,& bomb_hit,& bomb_run,& surprise_dummy_handler,bomb
    },
    {
         & surprise_dummy_handler, & ram_hit, & ram_run, & surprise_dummy_handler,ram
    
    }
};