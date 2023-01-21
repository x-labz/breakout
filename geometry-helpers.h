#pragma once

#include "inttypes.h"


typedef struct
{
    float x;
    float y;
} Point_t;

float areLinesCrossing(Point_t p1, Point_t p2,  Point_t v1, Point_t v2);

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

bool isOpposite( Point_t v, Point_t n ) ;