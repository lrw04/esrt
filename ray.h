#ifndef RAY_H
#define RAY_H

#include "vec.h"

struct ray {
    point o;
    v3 d;
    ray(point o, v3 d) : o(o), d(d) {}
    point operator()(real t) const;
};

#endif
