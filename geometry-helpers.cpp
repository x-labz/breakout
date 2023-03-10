#include "geometry-helpers.h"
#include "math.h"
#include "stdio.h"

// px + t * sx = bx + s* v2.x
// py + t * sy = by + s* v2.y
// t*sx-s*dx = bx - px
// t*sy-s*dy = by - py

float areLinesCrossing(Point_t p1, Point_t p2, Point_t v1, Point_t v2)
{
    float det = v1.x * -v2.y + v2.x * v1.y;
    if (det == 0)
        return -1;
    float detT = (p2.x - p1.x) * -v2.y + v2.x * (p2.y - p1.y);
    float detS = v1.x * (p2.y - p1.y) - (p2.x - p1.x) * v1.y;
    float t = detT / det;
    float s = detS / det;
    return t >= 0 && s >= 0 && s <= 1  && t<=1 ? t : -1;
  
}

bool isOpposite( Point_t v, Point_t n ) {
    if (  n.x == 0 && sgn(v.y) !=0 && sgn(v.y) != sgn(n.y)    ) return true;
    if (  n.y == 0 && sgn(v.x) !=0 && sgn(v.x) != sgn(n.x)    ) return true;
    return false;
}   