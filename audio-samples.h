#pragma once

#include "sound-knock.h"

enum {
    AUDIO_GET_READY,
    AUDIO_GAME_OVER,
    AUDIO_WIN
};

static const char * audio_filename_get_ready = "music/breakout+/0.raw" ;
static const char * audio_filename_game_over = "music/breakout+/1.raw" ;
static const char * audio_filename_win = "music/breakout+/2.raw" ;

static const char * audio_filenames[] = {
    audio_filename_get_ready,
    audio_filename_game_over,
    audio_filename_win
};

enum {
    AUDIO_SFX_KNOCK
};


