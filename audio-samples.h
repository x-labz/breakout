#pragma once

#include "sound-knock.h"

enum {
    AUDIO_GET_READY,
    AUDIO_GAME_OVER,
    AUDIO_WIN,
    AUDIO_APPEAR,
    AUDIO_PICKUP,
    AUDIO_BOMB,
    AUDIO_DEFEAT
};

static const char * audio_filename_get_ready = "music/breakout+/0.raw" ;
static const char * audio_filename_game_over = "music/breakout+/1.raw" ;
static const char * audio_filename_win = "music/breakout+/2.raw" ;
static const char * audio_filename_appear = "music/breakout+/3.raw" ;
static const char * audio_filename_pickup = "music/breakout+/4.raw" ;
static const char * audio_filename_bomb = "music/breakout+/5.raw" ;
static const char * audio_filename_defeat = "music/breakout+/6.raw" ;

static const char * audio_filenames[] = {
    audio_filename_get_ready,
    audio_filename_game_over,
    audio_filename_win,
    audio_filename_appear,
    audio_filename_pickup,
    audio_filename_bomb,
    audio_filename_defeat
};

enum {
    AUDIO_SFX_KNOCK
};


