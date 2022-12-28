#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>

#include "vec.h"

struct interval {
    real l, r;
    bool nonempty() const;
};

interval closure(interval a, interval b);
interval intersection(interval a, interval b);
bool element_of(real x, interval s);

const interval reals = {-INFINITY, INFINITY};
const interval empty_interval = {INFINITY, -INFINITY};

#endif
