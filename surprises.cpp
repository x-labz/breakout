#include "surprises.h"

void surprise_dummy_handler(Surprise_t * surprise_p, Breakout_store_t * p) {
};

void hearth_generate(Surprise_t * surprise_p, Breakout_store_t * p) {
    if (p->lives == 3) {
        surprise_p->type = SURPRISE_NONE;
        surprise_p->status = SURPRISE_STATUS_OFF;
    }
};
void hearth_run(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->status = SURPRISE_STATUS_OFF;
    surprise_p->type = SURPRISE_NONE;
};
void hearth_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
    p->lives++;
};

void inc_speed_generate(Surprise_t * surprise_p, Breakout_store_t * p) {
    
};
void inc_speed_run(Surprise_t * surprise_p, Breakout_store_t * p) {
    
};
void inc_speed_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->lifetime = 5000;
    p->ball_speed_x *=1.33;
    p->ball_speed_y *=1.33;
};

void inc_speed_destroy(Surprise_t * surprise_p, Breakout_store_t * p) {
    p->ball_speed_x /=1.33;
    p->ball_speed_y /=1.33;
};

void inc_paddle_w_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->lifetime = 10000;
    p->paddle_width = PADDLE_W * 2 ;
};

void inc_paddle_w_destroy(Surprise_t * surprise_p, Breakout_store_t * p) {
    p->paddle_width = PADDLE_W;
};

void bomb_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
     surprise_p->lifetime = 3000;
     surprise_p->progress = 0;
}

void ram_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
     surprise_p->lifetime = 3000;
     p->disableBrickBounce = true ;
}

void ram_run(Surprise_t * surprise_p, Breakout_store_t * p) {
     if(p->disableBrickBounce == false){
        surprise_p->status = SURPRISE_STATUS_OFF;
        surprise_p->type = SURPRISE_NONE;
    }
}

void bomb_run(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->progress += SURPRISE_BOMB_SPEED ;
    if (surprise_p->progress > SURPRISE_BOMB_DIST) {
        surprise_p->status = SURPRISE_STATUS_OFF;
        surprise_p->type = SURPRISE_NONE;
    }
    for (uint8_t i = 0; i != X_CNT * Y_CNT; i++) {

         Brick_t * brick = &(p->bricks[i]);

         if (brick->type == 0) {
             continue;
         }
         int16_t dx = surprise_p->x - brick->x ;
         int16_t dy = surprise_p->y - brick->y ;
         if (( surprise_p->progress + H ) * ( surprise_p->progress + H ) > dx*dx + dy*dy ) {
             brick->type = 0;
         }
    }
}

void penta_hit(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->lifetime = 5000;
    surprise_p->progress = SURPRISE_PENTA_BRICK_COUNT * SURPRISE_PENTA_BRICK_PROGRESS + 1;
}

void penta_run(Surprise_t * surprise_p, Breakout_store_t * p) {
    surprise_p->progress--;
    if (surprise_p->progress % SURPRISE_PENTA_BRICK_PROGRESS == 0 && surprise_p->progress > 0 ) {
        uint8_t results[16] ;
        uint8_t resultIndex = 0;
        for(uint16_t i=0; i!= X_CNT * Y_CNT && resultIndex < 15; i++) {
            if ( p->bricks[i].type == BRICK_REBORN ) p->bricks[i].type = BRICK_LIGHT ;
            if ( p->bricks[i].type == BRICK_OFF ) {
                results[resultIndex] = i;
                resultIndex++;
            }
        }
        if (resultIndex == 1 || resultIndex == 2) {
            p->bricks[results[0]].type = BRICK_REBORN;
        }
         if (resultIndex > 2) {
            uint8_t targetIndex = HAL::getRandom(resultIndex-1);
            p->bricks[results[targetIndex]].type = BRICK_REBORN;
        }
        
    }
    
    if (surprise_p->progress == 0) {
        surprise_p->status = SURPRISE_STATUS_OFF;
        surprise_p->type = SURPRISE_NONE;
        
        for(uint16_t i=0; i!= X_CNT * Y_CNT; i++) {
            if ( p->bricks[i].type == BRICK_REBORN ) p->bricks[i].type = BRICK_LIGHT ;
        }
    }
}