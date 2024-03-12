#ifndef SDF_HEADER
#define SDF_HEADER

#include <cmath>
#include "some_utils.h"

float ball_sdf(flt4 x, flt4 c, float r) {
    return std::sqrt(dot(x-c, x-c)) - r;
}

#endif
