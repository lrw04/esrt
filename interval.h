#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>

#include "vec.h"

struct interval {
    real l, r;
    bool nonempty() const;
};

interval bound(interval a, interval b);
interval intersection(interval a, interval b);

const interval reals = {-INFINITY, INFINITY};

#endif
