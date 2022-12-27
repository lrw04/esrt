#ifndef HIT_H
#define HIT_H

#include "vec.h"

struct hit {
    point p;
    v3 n;
    real t, u, v;
};

#endif
