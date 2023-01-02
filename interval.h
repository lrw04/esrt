#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>

#include "vec.h"

struct interval {
    real l, r;
    bool nonempty() const;
};

interval closure(const interval& a, const interval& b);
interval intersection(const interval& a, const interval& b);
bool element_of(real x, const interval& s);

const interval reals = {-INFINITY, INFINITY};
const interval empty_interval = {INFINITY, -INFINITY};

#endif
