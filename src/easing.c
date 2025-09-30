#include "easing.h"

/*
arguments:
t = current time
b = start value
c = change in value
d = duration
*/

float EaseOutQuad(float t, float b, float c, float d) {
    t /= d;
    return -c * t*(t-2) + b;
}

