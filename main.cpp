
#include "Pokitto.h"
#include "breakout_systems.h"
#include "breakout-store.h"
#include "breakout_render.h"

int main()
{
    using PC = Pokitto::Core;

    PC::begin();

    Breakout_store_t store;
    breakout_init(&store);

    while (PC::isRunning())
    {
        if (!PC::update())
            continue;

        breakout_render(&store);
        breakout_run();
    }

    return 0;
}
