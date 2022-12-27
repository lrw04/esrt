#include "interval.h"

#include <algorithm>

bool interval::nonempty() const {
    return l < r;
}

interval bound(interval a, interval b) {
    return {std::min(a.l, b.l), std::max(a.r, b.r)};
}

interval intersection(interval a, interval b) {
    return {std::max(a.l, b.l), std::min(a.r, b.r)};
}
