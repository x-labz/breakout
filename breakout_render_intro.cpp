#include "breakout_render_intro.h"
#include "math-helpers.h"
#include <string.h>
#include "stdio.h"

static
const uint8_t lines[] = {
    5,
    5,
    6,
    6,
    7,
    7,
    7,
    6,
    6,
    5,
    5,
};

static const char * intro_text = "Hey!      Welcome, X-LABZ presents Breakout+, a brand new demake of the atari classic arcade game... The game is targeted both to POKITTO and Lilygo TTGO T-Wristband, a supercool ESP32 based smart watch... stay tuned! Greetings to all POKITTO game makers ;-) cheers!       ";
static const char * title = "b r e a k o u t +" ;
static char render_text[64];
static uint16_t cnt = 0;
static int16_t offset = 0;

static uint8_t char_w;
static int16_t text_offset = DISP_TOTAL_X - char_w;


void render_intro(void) {
    offset =  10 + (DISP_Y - 20) / 2 + sin_table[cnt >> 2] * (DISP_Y / 2 - 20);
    for (uint8_t i = 0; i != sizeof(lines); i++) {
        HAL::displaySetColor(lines[i]);
        HAL::displayDrawLine(0, offset + i, DISP_TOTAL_X,  offset + i);
    }
    cnt++;
    if (cnt == 72 << 2) {
        cnt = 0;
    }

    char_w = HAL::getFontCharX();


    HAL::displaySetColor(12);

    int16_t char_offset = 0;
    while (text_offset + char_offset * char_w <= DISP_TOTAL_X - char_w * 2) {
        int16_t x0 = text_offset + char_offset * char_w;
        if (x0 > 0) {
            HAL::displaySetCursor(x0, DISP_Y / 2 + sin_table[(x0>>1)%72] * 12);
            char text[2] = {
                0,
                0
            };
            strncpy(text, intro_text + char_offset, 1);
            HAL::displayPrint(text);
        }

        if (char_offset < strlen(intro_text)) {
            char_offset++;
        }
    }
    
    uint8_t title_w = strlen(title) * (char_w ) ; 
 
    HAL::displaySetColor(9);
    HAL::displaySetCursor(0 + (1.0 + sin_table[cnt >>2]) / 2 * (DISP_TOTAL_X - title_w) ,DISP_Y/4);
    HAL::displayPrint((char *)title);
    

    text_offset--;
    if (text_offset < 0 && char_offset == strlen(intro_text)) {
        text_offset = DISP_TOTAL_X - char_w;
        char_offset = 0;
    }

}