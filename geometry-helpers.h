#pragma once

#include "inttypes.h"


typedef struct
{
    float x;
    float y;
} Point_t;

float areLinesCrossing(Point_t p1, Point_t p2,  Point_t v1, Point_t v2);
