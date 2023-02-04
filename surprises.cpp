#include "surprises.h"

void surprise_dummy_handler(Surprise_t * surprise_p, Breakout_store_t * p) {
};

void hearth_generate(Surprise_t * surprise_p, Breakout_store_t * p) {
    if (p->lives == 3) {
        surprise_p->type = SURPRISE_NONE;
    }
};
void hearth_run(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->status = SURPRISE_STATUS_OFF;
    surprise_p->type = SURPRISE_NONE;
};
void hearth_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
    p->lives++;
    surprise_p->status = SURPRISE_STATUS_OFF;
    surprise_p->type = SURPRISE_NONE;
};

void inc_speed_generate(Surprise_t * surprise_p, Breakout_store_t * p) {
    
};
void inc_speed_run(Surprise_t * surprise_p, Breakout_store_t * p) {
    
};
void inc_speed_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->lifetime = 5000;
    p->ball_speed_x *=2;
    p->ball_speed_y *=2;
};

void inc_speed_destroy(Surprise_t * surprise_p, Breakout_store_t * p) {
    p->ball_speed_x /=2;
    p->ball_speed_y /=2;
};

void inc_paddle_w_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->lifetime = 10000;
    p->paddle_width = PADDLE_W * 2 ;
};

void inc_paddle_w_destroy(Surprise_t * surprise_p, Breakout_store_t * p) {
    p->paddle_width = PADDLE_W;
};