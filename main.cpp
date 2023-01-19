#include "Pokitto.h"


#include "breakout_systems.h"
#include "breakout-store.h"
#include "breakout_render.h"

int main() {
    using PC = Pokitto::Core;
    using PD = Pokitto::Display;
    PC::begin();
    PD::persistence = false;
    PD::invisiblecolor = 0;

    Breakout_store_t store;
    breakout_init( & store);

    while (PC::isRunning()) {
        if (!PC::update())
            continue;
        breakout_render( & store);
        breakout_run();
    }

    return 0;
}