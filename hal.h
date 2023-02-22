#pragma once

#define COMPILE_TO_POKITTO

#ifdef   COMPILE_TO_POKITTO

#include "hal-pokitto.h"

#else  

#include "hal-watch.h"

#endif  // COMPILE_TO_POKITTO

