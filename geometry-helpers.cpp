#include "geometry-helpers.h"
#include "math.h"
#include "stdio.h"

// px + t * sx = bx + s* v2.x
// py + t * sy = by + s* v2.y
// t*sx-s*dx = bx - px
// t*sy-s*dy = by - py

int32_t areLinesCrossing(Point_t p1, Point_t p2, Point_t v1, Point_t v2)
{
    float det = v1.x * -v2.y + v2.x * v1.y;
    if (det == 0)
        return -1;
    float detT = (p2.x - p1.x) * -v2.y + v2.x * (p2.y - p1.y);
    float detS = v1.x * (p2.y - p1.y) - (p2.x - p1.x) * v1.y;
    float t = detT / det;
    float s = detS / det;
    //  printf(" s: %.1f,t:%.1f \n", s, t);
    return t >= 0 && s >= 0 && s <= 1  && t<=1 ? t : -1;
    // return t >= 0 && s >= 0 ? t : -1;
}