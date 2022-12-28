#include "interval.h"

#include <algorithm>

bool interval::nonempty() const { return l < r; }

interval closure(interval a, interval b) {
    if (a.nonempty() && b.nonempty())
        return {std::min(a.l, b.l), std::max(a.r, b.r)};
    if (a.nonempty()) return a;
    if (b.nonempty()) return b;
    return empty_interval;
}

interval intersection(interval a, interval b) {
    return {std::max(a.l, b.l), std::min(a.r, b.r)};
}
