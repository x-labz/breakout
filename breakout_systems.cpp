 #include "Pokitto.h"
 #include "breakout_systems.h"
 #include "geometry-helpers.h"
 #include "hal.h"
 #include "patterns.h"
 #include "stdio.h"

 Breakout_store_t * store;

 uint32_t last_ticks_stamp;
 uint32_t ticks;
 uint32_t last_ticks;

 void breakout_init(Breakout_store_t * p) {
     if (p != NULL ) {
         store = p;
     }
     
     *store = {
         .game_state = GAME_STATE_RDY,
         .bricks = {},
         .fps = 0,
         .paddle_x = 0,
         .paddle_speed = 0,
         .ball_x = (DISP_X / 2 - 1),
         .ball_y = (DISP_Y / 2 - 1) + 20,
         .ball_speed_x = 0.25,
         .ball_speed_y = -0.65,
         .brick_x = -1,
         .brick_y = -1,
         .coll_brick_p1 = {
             0,
             0
         },
         .coll_brick_p2 = {
             0,
             0
         },
         .coll_brick_valid = false
     };

     createPattern(store, 0);

     last_ticks_stamp = HAL::getTimeStamp();
     ticks = 0;
     last_ticks = 0;
 }

 void calc_fps(void) {
     ticks++;
     uint32_t ts = HAL::getTimeStamp();
     if (ts > last_ticks_stamp + 1000) {
         last_ticks_stamp = ts;
         store->fps = ticks - last_ticks;
         last_ticks = ticks;
     }
 }

 float bounce(float speed) {
     float variance = (rand() % 100) / 1000;
    //  printf("%.1f", variance);
     return speed * -(1 + variance);
 }

 void move_paddle(void) {
     int16_t pitch = HAL::getPaddlePitch();
     if (pitch > 25)
         pitch = 25;
     if (pitch < -25)
         pitch = -25;

     store->paddle_speed = pitch / 5;
     int16_t x = store->paddle_x;
     x += store->paddle_speed;
     if (x < 0)
         x = 0;
     if (x > DISP_X - PADDLE_W - 2)
         x = DISP_X - PADDLE_W - 2;
     store->paddle_x = x;
 }

 void move_ball(void) {
     store->ball_x += store->ball_speed_x;
     store->ball_y += store->ball_speed_y;
 }

 void bounce_wall(void) {
     if (store->ball_x < (BALL_R)) {
         store->ball_x = (BALL_R);
         store->ball_speed_x = bounce(store->ball_speed_x);
     }
     if (store->ball_y < (BALL_R)) {
         store->ball_y = (BALL_R);
         store->ball_speed_y = bounce(store->ball_speed_y);
     }
     if (store->ball_x > ((DISP_X - 1 - BALL_R))) {
         store->ball_x = (DISP_X - 1 - BALL_R);
         store->ball_speed_x = bounce(store->ball_speed_x);
     }
     if (store->ball_y > (DISP_Y - 1)) {
         store->ball_speed_x = 0;
         store->ball_speed_y = 0;
     }

 }

 void check_fall(void) {
     int16_t paddle_y = DISP_Y - 1 - DASH_HEIGHT - PADDLE_H;
     if (store->ball_y > (DISP_Y - 1 - DASH_HEIGHT)) {
         store->game_state = GAME_STATE_GAME_OVER;
     }
 }

 void check_win(void) {
     uint8_t count = 0;
     for (uint8_t i = 0; i != X_CNT * Y_CNT; i++) {
         Brick_t brick = store->bricks[i];
         if (brick.type > 0) {
             count++;
         }
     }
     if (count == 0) {
         store->game_state = GAME_STATE_WIN;
     }
 }

 void bounce_paddle(void) {
     int16_t paddle_y = DISP_Y - 1 - DASH_HEIGHT - PADDLE_H;
     if (store->ball_y > ((paddle_y - BALL_R)) && store->ball_x >= (store->paddle_x) && store->ball_x <= ((store->paddle_x + PADDLE_W))) {
         store->ball_y = (paddle_y - BALL_R);
         store->ball_speed_y = bounce(store->ball_speed_y);
         store->ball_speed_x += (float)store->paddle_speed / 10.0;

        //  printf("S:%d", (int)(store->ball_speed_x * 1000));
     }
 }

 bool calc_brick(uint8_t brickID) {

     Brick_t brick = store->bricks[brickID];

     Point_t result_p1, result_p2;
     // float t_result = 999999;
     uint8_t dir_cnt = 0;
     Point_t dir[4] = {
         {
             W,
             0
         },
         {
             0,
             H
         },
         {
             0,
             -H,
         },
         {

             -W,
             0
         }
     };

     // 1--2
     // .  .
     // 3--4

     // printf("------\n");
     // printf("brick (%d,%d) \n", x, y);
     store->coll_brick_valid = false;
     for (uint8_t ry = 0; ry != 2; ry++) {
         for (uint8_t rx = 0; rx != 2; rx++) {
             int8_t ball_speed_x_sign_neg = store->ball_speed_x < 0 ? -1 : 1;
             int8_t ball_speed_y_sign_neg = store->ball_speed_y < 0 ? -1 : 1;
             Point_t ball_p = {
                 (store->ball_x - (store->ball_speed_x + BALL_R * ball_speed_x_sign_neg)),
                 (store->ball_y - (store->ball_speed_y + BALL_R * ball_speed_y_sign_neg))
             };
             Point_t ball_v = {
                 store->ball_speed_x + BALL_R * ball_speed_x_sign_neg * 2,
                 store->ball_speed_y + BALL_R * ball_speed_y_sign_neg * 2
             };
             Point_t brick_p = {
                 brick.x + rx * W,
                 brick.y + ry * H
             };
             Point_t brick_v = dir[dir_cnt];



             float t = areLinesCrossing(ball_p, brick_p, ball_v, brick_v);
             if (t >= 0) {
                 // t_result = t;
                 result_p1.x = brick_p.x;
                 result_p1.y = brick_p.y;
                 result_p2.x = brick_p.x + brick_v.x;
                 result_p2.y = brick_p.y + brick_v.y;
                 store->coll_brick_valid = true;

                 store->coll_brick_p1.x = result_p1.x;
                 store->coll_brick_p1.y = result_p1.y;
                 store->coll_brick_p2.x = result_p2.x;
                 store->coll_brick_p2.y = result_p2.y;
                 // printf("(%f,%f)-(%.2f,%.2f) %.2f \n", brick_p.x, brick_p.y, brick_v.x, brick_v.y, t);

                 if (dir[dir_cnt].x) {
                     store->ball_speed_y = bounce(store->ball_speed_y);
                 }
                 if (dir[dir_cnt].y) {
                     store->ball_speed_x = bounce(store->ball_speed_x);
                 }
                 return true;
             }

             dir_cnt++;
         }
     }

     return false;
     // if (store->coll_brick_valid) {
     //     store->coll_brick_p1.x = result_p1.x;
     //     store->coll_brick_p1.y = result_p1.y;
     //     store->coll_brick_p2.x = result_p2.x;
     //     store->coll_brick_p2.y = result_p2.y;
     //     // printf("--Result:%d,%d-%d,%d\n", result_p1.x, result_p1.y, result_p2.x, result_p2.y);
     // }
 }

 void calc_brick_coll(void) {
     for (uint8_t i = 0; i != X_CNT * Y_CNT; i++) {

         Brick_t brick = store->bricks[i];
         // store->bricks[i].type = 1;
         if (brick.blocker > 0) {
             store->bricks[i].blocker--;
         }
         if (brick.type > 0 && brick.blocker == 0 && (store->ball_x > brick.x - BALL_R && store->ball_x < brick.x + X_GAP + BALL_R) &&
             (store->ball_y > brick.y - BALL_R && store->ball_y < brick.y + Y_GAP + BALL_R)) {

             bool coll = calc_brick(i);
             if (coll) {
                 if (store->bricks[i].type > 1) {
                     store->bricks[i].blocker = 10;
                 }
                 store->bricks[i].type--;

             }
         }
     }
 }

 void handleStart(void) {
     if (store->game_state == GAME_STATE_RDY && HAL::getAButton()) {
         store->game_state = GAME_STATE_RUN;
     }
 }

 void handleGameOver(void) {
     if (store->game_state == GAME_STATE_GAME_OVER && HAL::getAButton()) {
         breakout_init((Breakout_store_t*)NULL);
        //  store->game_state = GAME_STATE_RDY;
     }
 }

 bool breakout_run(void) {
     if (store->game_state == GAME_STATE_RUN) {
         calc_fps();
         move_paddle();
         move_ball();
         bounce_wall();
         bounce_paddle();
         calc_brick_coll();
         check_fall();
         check_win();
     }
     handleStart();
     handleGameOver();

     return true;
 }