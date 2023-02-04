#pragma once     

#include "breakout-store.h"
#include "surprises.h"

void surpriseSystem( Breakout_store_t * p);
void generateSurprise( Breakout_store_t * p ) ;
void run( Breakout_store_t * p);
void checkSurpriseHit( Breakout_store_t * p);