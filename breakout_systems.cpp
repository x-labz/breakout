#include "math.h"
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
     if (p != NULL) {
         store = p;
     }

     * store = {
         .surprise = {0,0,0,0,0},
         .lives = 1,
         .score = 0,
         .lastBounceWasBrick = false,
         .game_state = GAME_STATE_START,
         .bricks = {},
         .fps = 0,
         .paddle_x = (DISP_X - PADDLE_W) / 2,
         .paddle_speed = 0,
         .ball_x = (DISP_X / 2 - 1),
         .ball_y = (DISP_Y / 2 - 1) + 40,
         .ball_speed_x = (float) HAL::getRandom(100) / 200 - 0.25,
         .ball_speed_y = -0.95,
        //  .brick_x = -1,
        //  .brick_y = -1,
         //  .coll_brick_p1 = {
         //      0,
         //      0
         //  },
         //  .coll_brick_p2 = {
         //      0,
         //      0
         //  },
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
     float variance = HAL::getRandom(100) / 1000;

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
     if (store->ball_y > (DISP_Y - 1) && store->lives > 0) {
         store->ball_y = (DISP_Y - 1 );
         store->ball_speed_y = bounce(store->ball_speed_y);
         store->lives--;
     }

 }

 void check_fall(void) {
    //  int16_t paddle_y = DISP_Y - 1 - DASH_HEIGHT - PADDLE_H;
     if (store->ball_y > (DISP_Y - 1 - DASH_HEIGHT) && store->ball_speed_y > 0 && store->lives == 0 ) {
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
     if (store->ball_y >= ((paddle_y - BALL_R)) && store->ball_x >= (store->paddle_x ) && store->ball_x <= ((store->paddle_x + PADDLE_W ))) {
         store->ball_y = (paddle_y - BALL_R);
         float accelerate = (float) store->paddle_speed / 20.0;
         store->ball_speed_y = bounce(store->ball_speed_y) - abs(accelerate);
         store->ball_speed_x += accelerate;
         store->lastBounceWasBrick = false;
     }
 }

 bool calc_brick(uint8_t brickID) {

     Brick_t brick = store->bricks[brickID];

     Point_t result_p1, result_p2;
     float t_result = 999999;
     uint8_t dir_cnt = 0;
     Point_t dir[4] = {
         {
             W +  2 *BALL_R,
                 0
         },
         {
             0,
             H + 2 * BALL_R
         },
         {
             0,
             -H - 2 * BALL_R,
         },
         {

             -W - 2 *BALL_R,
             0
         }
     };

     Point_t normals[4] {
         {
             0,
             -1
         }, {
             1,
             0
         }, {-1,
             0
         }, {
             0,
             1
         }
     };

     // 1--2
     // .  .
     // 3--4

     store->coll_brick_valid = false;
     int8_t result_dir = -1;
     for (uint8_t ry = 0; ry != 2; ry++) {
         for (uint8_t rx = 0; rx != 2; rx++) {
             float fract = (float) BALL_R / (abs(store->ball_speed_x) + abs(store->ball_speed_y));
             float x_add = store->ball_speed_x / fract * (float)(BALL_R);
             float y_add = store->ball_speed_y / fract * (float)(BALL_R);
             Point_t ball_p = {
                 store->ball_x - store->ball_speed_x - x_add,
                 store->ball_y - store->ball_speed_y - y_add
             };
             Point_t ball_v = {
                 store->ball_speed_x + 2 * x_add,
                 store->ball_speed_y + 2 * y_add
             };
             Point_t brick_p = {
                 brick.x - BALL_R + rx * (W + 2 * BALL_R ),
                 brick.y - BALL_R + ry * (H + 2 * BALL_R )
             };
             Point_t brick_v = dir[dir_cnt];

             float t = areLinesCrossing(ball_p, brick_p, ball_v, brick_v);
             bool opposite = isOpposite(ball_v, normals[dir_cnt]);
             if (t >= 0 && t < t_result && opposite) {
                //  printf("opp: %d , %d,%d , n: %d,%d \n ", opposite, 
                //   (int)(ball_v.x * 100.0F) ,
                //   (int)(ball_v.y * 100.0F) ,
                //     (int)(normals[dir_cnt].x * 100.0F) ,
                //      (int)(normals[dir_cnt].y * 100.0F) 
                //  ) ;
                 t_result = t;
                 store->coll_brick_valid = true;
                 result_dir = dir_cnt;
             }

             dir_cnt++;
         }
     }

     if (store->coll_brick_valid ) {

         if (dir[result_dir].x) {
            //  printf("y bounce %d \n", (int)(store->ball_speed_y * 100.0F) );
             store->ball_speed_y = bounce(store->ball_speed_y);
         }
         if (dir[result_dir].y) {
            //  printf("x bounce \n");
             store->ball_speed_x = bounce(store->ball_speed_x);
         }

     }

     return result_dir >= 0;

 }

 void calc_brick_coll(void) {
     for (uint8_t i = 0; i != X_CNT * Y_CNT; i++) {

         Brick_t brick = store->bricks[i];

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
                 store->score += store->lastBounceWasBrick ? 20 : 10;
                 store->lastBounceWasBrick = true;
             }
         }
     }
 }

 void handleStart(void) {
     if (store->game_state == GAME_STATE_RDY && HAL::getAButton()) {
         store->game_state = GAME_STATE_RUN;
     }
     if (store->game_state == GAME_STATE_START && HAL::getAButton()) {
         store->game_state = GAME_STATE_RDY;
     }
 }

 void handleGameOver(void) {
     if ((store->game_state == GAME_STATE_GAME_OVER || store->game_state == GAME_STATE_WIN) && HAL::getAButton()) {
         breakout_init((Breakout_store_t * ) NULL);
         store->game_state = GAME_STATE_RDY ;
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