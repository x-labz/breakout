#pragma once

#include "inttypes.h"
#include "FixedPoints.h"
#include "FixedPointsCommon.h"


typedef struct
{
    SQ15x16 x;
    SQ15x16 y;
} Point_t;

SQ15x16 areLinesCrossing(Point_t p1, Point_t p2,  Point_t v1, Point_t v2);

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

bool isOpposite( Point_t v, Point_t n ) ;